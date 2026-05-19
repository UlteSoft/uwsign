#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
workdir="${UWSIGN_TEST_WORKDIR:-/tmp/uwsigntest}"
wasi_sysroot="${WASI_SYSROOT:-/Users/liyinan/Documents/MacroModel/src/wasi-libc/build-mvp/sysroot}"

mkdir -p "${workdir}"
rm -rf "${workdir:?}"/*

cd "${repo_root}"
xmake f -m debug --use-llvm-compiler=y
xmake -y

uwsign_bin="${repo_root}/build/macosx/arm64/debug/uwsign"
if [[ ! -x "${uwsign_bin}" ]]; then
	echo "uwsign binary was not found" >&2
	exit 1
fi

cd "${workdir}"

cat > control.cc <<'CC'
extern "C" int control_add(int a, int b)
{
	return a + b;
}
CC

if command -v clang++ >/dev/null 2>&1 && [[ -d "${wasi_sysroot}" ]]; then
	if ! clang++ -o control.wasm control.cc -Ofast -Wno-deprecated-ofast -s -flto -fuse-ld=lld -fno-rtti \
		-fno-unwind-tables -fno-asynchronous-unwind-tables -fno-exceptions --target=wasm32-wasip1 \
		--sysroot="${wasi_sysroot}" -L"${wasi_sysroot}/lib/wasm32-wasip1" -std=c++26 -mno-bulk-memory -mno-bulk-memory-opt \
		-mno-nontrapping-fptoint -mno-sign-ext -mno-mutable-globals -mno-multivalue -mno-reference-types \
		-mno-call-indirect-overlong > clang-wasm.log 2>&1; then
		printf '\x00\x61\x73\x6d\x01\x00\x00\x00' > control.wasm
	fi
else
	printf '\x00\x61\x73\x6d\x01\x00\x00\x00' > control.wasm
fi

openssl ecparam -name prime256v1 -genkey -noout -out key.pem >/dev/null 2>&1
openssl pkey -in key.pem -pubout -out pub.pem >/dev/null 2>&1
openssl req -new -x509 -key key.pem -out cert.pem -subj '/CN=uwsign-test' -days 1 >/dev/null 2>&1
openssl ecparam -name prime256v1 -genkey -noout -out root-key.pem >/dev/null 2>&1
openssl req -new -x509 -key root-key.pem -out root-cert.pem -subj '/CN=uwsign-test-root' -days 1 >/dev/null 2>&1
openssl ecparam -name prime256v1 -genkey -noout -out leaf-key.pem >/dev/null 2>&1
openssl req -new -key leaf-key.pem -out leaf.csr -subj '/CN=uwsign-test-leaf' >/dev/null 2>&1
openssl x509 -req -in leaf.csr -CA root-cert.pem -CAkey root-key.pem -CAcreateserial -out leaf-cert.pem -days 1 -sha256 >/dev/null 2>&1
cp root-cert.pem leaf-chain.pem

"${uwsign_bin}" --sign --input control.wasm --output signed1.wasm --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input signed1.wasm --key pub.pem
"${uwsign_bin}" --verify --input signed1.wasm --certificate cert.pem
"${uwsign_bin}" --verify --input signed1.wasm

cat control.wasm | "${uwsign_bin}" --sign --input - --wasm-output stdin_signed.wasm --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input stdin_signed.wasm --key pub.pem

"${uwsign_bin}" --sign --input control.wasm --wasm-output - --key key.pem --certificate cert.pem > stdout_signed.wasm
"${uwsign_bin}" --verify --input stdout_signed.wasm --key pub.pem

"${uwsign_bin}" --sign --input control.wasm --bundle - --key key.pem --certificate cert.pem > stdout_bundle.uwsign
"${uwsign_bin}" --verify --input control.wasm --bundle stdout_bundle.uwsign --key pub.pem

"${uwsign_bin}" --sign --input control.wasm --output-signature - --key key.pem --certificate cert.pem > stdout.sig
"${uwsign_bin}" --verify --input control.wasm --signature stdout.sig --key pub.pem

"${uwsign_bin}" --sign --input control.wasm --output-signature b64.sig --output-certificate b64-cert.pem --b64 --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input control.wasm --signature b64.sig --key pub.pem
python3 - <<'PY'
import base64
import base64
import json
from pathlib import Path

Path("b64-cert-decoded.pem").write_bytes(base64.b64decode(Path("b64-cert.pem").read_bytes()))
PY
cmp cert.pem b64-cert-decoded.pem >/dev/null

"${uwsign_bin}" --sign --input control.wasm --output chain_signed.wasm --key leaf-key.pem --certificate leaf-cert.pem --certificate-chain leaf-chain.pem --output-certificate-chain exported-chain.pem
"${uwsign_bin}" --verify --input chain_signed.wasm
"${uwsign_bin}" --verify --input chain_signed.wasm --certificate leaf-cert.pem --certificate-chain leaf-chain.pem
cmp leaf-chain.pem exported-chain.pem >/dev/null

"${uwsign_bin}" --sign --input signed1.wasm --output signed2.wasm --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input signed2.wasm --key pub.pem

"${uwsign_bin}" --sign --input control.wasm --wasm-output cosign_style.wasm --bundle bundle.uwsign --output-signature control.sig --output-certificate exported-cert.pem --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input control.wasm --bundle bundle.uwsign --key pub.pem
"${uwsign_bin}" --verify --input cosign_style.wasm --bundle bundle.uwsign --key pub.pem
"${uwsign_bin}" --verify --input control.wasm --signature control.sig --key pub.pem
cmp cert.pem exported-cert.pem >/dev/null

"${uwsign_bin}" --sign --input control.wasm --wasm-output cosign_legacy.wasm --bundle cosign_legacy.json --bundle-format cosign --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input control.wasm --bundle cosign_legacy.json --key pub.pem
"${uwsign_bin}" --verify --input cosign_legacy.wasm --key pub.pem
"${uwsign_bin}" --verify --input cosign_legacy.wasm

"${uwsign_bin}" --sign --input control.wasm --wasm-output cosign_legacy_pubkey.wasm --bundle cosign_legacy_pubkey.json --bundle-format cosign --key key.pem
"${uwsign_bin}" --verify --input control.wasm --bundle cosign_legacy_pubkey.json
"${uwsign_bin}" --verify --input cosign_legacy_pubkey.wasm

"${uwsign_bin}" --sign --input signed2.wasm --wasm-output replaced.wasm --bundle replaced.uwsign --replace --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input replaced.wasm --key pub.pem

python3 - <<'PY'
import base64
import json
from pathlib import Path

def enc_u32(value: int) -> bytes:
    out = bytearray()
    while True:
        b = value & 0x7f
        value >>= 7
        if value:
            b |= 0x80
        out.append(b)
        if not value:
            return bytes(out)

module = Path("control.wasm").read_bytes()
name = b"not-uwsign"
payload = b"other-custom-bundle"
section_payload = enc_u32(len(name)) + name + payload
Path("other_custom.wasm").write_bytes(module + b"\x00" + enc_u32(len(section_payload)) + section_payload)
PY

"${uwsign_bin}" --sign --input other_custom.wasm --wasm-output other_custom_replaced.wasm --replace --key key.pem --certificate cert.pem
"${uwsign_bin}" --verify --input other_custom_replaced.wasm --key pub.pem

python3 - <<'PY'
import base64
import json
from pathlib import Path

data = Path("signed2.wasm").read_bytes()
count = data.count(b"wasm_uwsign")
if count != 2:
    raise SystemExit(f"expected 2 wasm_uwsign sections, got {count}")

replaced = Path("replaced.wasm").read_bytes()
replaced_count = replaced.count(b"wasm_uwsign")
if replaced_count != 1:
    raise SystemExit(f"expected 1 replaced wasm_uwsign section, got {replaced_count}")

cosign_style = Path("cosign_style.wasm").read_bytes()
cosign_style_count = cosign_style.count(b"wasm_uwsign")
if cosign_style_count != 1:
    raise SystemExit(f"expected 1 cosign-style wasm_uwsign section, got {cosign_style_count}")

cosign_legacy = Path("cosign_legacy.json").read_bytes()
if b'"base64Signature"' not in cosign_legacy or b'"cert"' not in cosign_legacy:
    raise SystemExit("cosign legacy bundle did not contain expected fields")
cosign_legacy_wasm = Path("cosign_legacy.wasm").read_bytes()
cosign_legacy_count = cosign_legacy_wasm.count(b"wasm_uwsign")
if cosign_legacy_count != 1:
    raise SystemExit(f"expected 1 cosign legacy wasm_uwsign section, got {cosign_legacy_count}")

cosign_legacy_pubkey = Path("cosign_legacy_pubkey.json").read_bytes()
if b'"base64Signature"' not in cosign_legacy_pubkey or b'"cert"' not in cosign_legacy_pubkey:
    raise SystemExit("cosign legacy public-key bundle did not contain expected fields")
cosign_legacy_pubkey_cert = base64.b64decode(json.loads(cosign_legacy_pubkey)["cert"])
if b"BEGIN PUBLIC KEY" not in cosign_legacy_pubkey_cert:
    raise SystemExit("cosign legacy public-key bundle did not contain PEM public key material")
cosign_legacy_pubkey_wasm = Path("cosign_legacy_pubkey.wasm").read_bytes()
cosign_legacy_pubkey_count = cosign_legacy_pubkey_wasm.count(b"wasm_uwsign")
if cosign_legacy_pubkey_count != 1:
    raise SystemExit(f"expected 1 cosign legacy public-key wasm_uwsign section, got {cosign_legacy_pubkey_count}")

other_custom_replaced = Path("other_custom_replaced.wasm").read_bytes()
if b"not-uwsign" not in other_custom_replaced:
    raise SystemExit("non-uwsign custom section was stripped by --replace")
other_custom_replaced_count = other_custom_replaced.count(b"wasm_uwsign")
if other_custom_replaced_count != 1:
    raise SystemExit(f"expected 1 replacement wasm_uwsign section, got {other_custom_replaced_count}")

tampered = bytearray(data)
header = b"\x00asm\x01\x00\x00\x00"
pos = tampered.find(header)
if pos != 0:
    raise SystemExit("not a wasm file")

needle = b"wasm_uwsign"
signature_name = tampered.find(needle)
for i in range(8, len(tampered)):
    if signature_name <= i < signature_name + len(needle):
        continue
    tampered[i] ^= 0x01
    break
else:
    raise SystemExit("did not find byte to tamper")

Path("tampered.wasm").write_bytes(tampered)
PY

if "${uwsign_bin}" --verify --input tampered.wasm --key pub.pem; then
	echo "tampered module unexpectedly verified" >&2
	exit 1
fi

echo "[pass] wasm cli integration test"
