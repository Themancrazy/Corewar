#include "vm.h"

static void    h_rev_bytes(void *ptr, size_t n)
{
	size_t	i;
	size_t  half;
	uint8_t *tmp;
	uint8_t swap;

	i = 0;
	half = n / 2;
	tmp = (uint8_t *)ptr;
	while (i < half)
	{
		swap = tmp[i];
		tmp[i] = tmp[n - i - 1];
		tmp[n - i - 1] = swap;
		++i;
	}
}

static void			champ_init(t_cw *cw, t_hdr *hdr, int fd, int champ_num)
{
	t_champ		*new_champ;

	if (cw->champions[champ_num].manual_assign == 1)
		new_champ = &(cw->champions[champ_num]);
	else
		new_champ = &(cw->tmp_champ[champ_num]);
	new_champ->name = ft_strdup(hdr->prog_name);
	new_champ->comment = ft_strdup(hdr->comment);
	new_champ->prog_number = champ_num + 1;
	new_champ->prog_size = hdr->prog_size;
	new_champ->fd = fd;
}

static void			champ_read_header(t_hdr *hdr, int fd)
{
	off_t	file_size;

	if (!(file_size = lseek(fd, 0, SEEK_END)))
		send_error("Couldn't get size of file.\n");
	if ((size_t)file_size < sizeof(t_hdr))
		send_error("Invalid header size.\n");
	if (lseek(fd, 0, SEEK_SET) == -1)
		send_error("Couldnt set offset to 0.\n");
	if (read(fd, hdr, sizeof(t_hdr)) != sizeof(t_hdr))
		send_error("Error while reading the file.\n");
	h_rev_bytes(&hdr->magic, sizeof(hdr->magic));
	if (hdr->magic != COREWAR_EXEC_MAGIC)
		send_error("Magic is not correct.\n");
	h_rev_bytes(&hdr->prog_size, sizeof(hdr->prog_size));
	if (hdr->prog_size > CHAMP_MAX_SIZE)
		send_error("Size of champion is too big.\n");
}

static int			champ_check_file(char *filename, int *fd)
{
	int		len;
	char	*ext;

	len = (int)ft_strlen(filename);
	if (len < 4)
		send_error("Incorrect file name for champion.\n");
	ext = ft_strsub(filename, len - 4, 4);
	if (ft_strcmp(ext, ".cor"))
		send_error("Invalid extension.\n");
	if (!(*fd = open(filename, O_RDONLY)))
		send_error("File couldn't be opened.\n");
	free(ext);
	return (0);
}

void				champ_load(t_cw *cw, char *filename, int champ_num)
{
	int			fd;
	t_hdr		hdr;

	hdr = cw->header;
	champ_check_file(filename, &fd);
	champ_read_header(&hdr, fd);
	champ_init(cw, &  hdr, fd, champ_num);
}