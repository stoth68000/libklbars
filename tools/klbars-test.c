#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libklbars/klbars.h>

int main()
{
	struct kl_colorbar_context osd_ctx;
	int width=640, height=480;
	unsigned char *buf;

	/* Use the custom V210 stride required by the Decklink stack */
	int rowWidth = ((width + 47) / 48) * 128;
	fprintf(stderr, "row stride is %d\n", rowWidth);

	buf = malloc(rowWidth * height);
	memset(buf, 0, rowWidth * height);
	kl_colorbar_init(&osd_ctx, width, height, KL_COLORBAR_10BIT);
	kl_colorbar_fill_colorbars(&osd_ctx);
	kl_colorbar_finalize(&osd_ctx, buf, rowWidth);

	for (int i = 0; i < 32; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");

	int fd = open("foo.yuv", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0) {
		fprintf(stderr, "Failed to open output file\n");
		return 1;
	}
	write(fd, buf, rowWidth * height);
	close(fd);

	kl_colorbar_free(&osd_ctx);
	free(buf);
	return 0;
}
