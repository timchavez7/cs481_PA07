#include <stdio.h>
#include <stdlib.h>

struct ext2_super_block {
__le32 s_inodes_count;		 /* Inodes count */
__le32 s_blocks_count;		 /* Blocks count */
__le32 s_r_blocks_count; /* Reserved blocks count */
__le32 s_free_blocks_count; /* Free blocks count */
__le32 s_free_inodes_count; /* Free inodes count */
__le32 s_first_data_block; /* First Data Block */
__le32 s_log_block_size; /* Block size */
__le32 s_log_frag_size; /* Fragment size */
__le32 s_blocks_per_group; /* # Blocks per group */
__le32 s_frags_per_group; /* # Fragments per group */
__le32 s_inodes_per_group; /* # Inodes per group */
__le32 s_mtime;	 	 /* Mount time */
__le32 s_wtime;	 	 /* Write time */
__le16 s_mnt_count;	 	 /* Mount count */
__le16 s_max_mnt_count; /* Maximal mount count */
__le16 s_magic;	 	 /* Magic signature */
__le16 s_state;	 	 /* File system state */
__le16 s_errors;	 	 /* Behaviour when detecting errors */
__le16 s_minor_rev_level; /* minor revision level */
__le32 s_lastcheck;	 	 /* time of last check */
__le32 s_checkinterval; /* max. time between checks */
__le32 s_creator_os;	 	 /* OS */
__le32 s_rev_level;	 	 /* Revision level */
__le16 s_def_resuid;	 	 /* Default uid for reserved blocks */
__le16 s_def_resgid;	 	 /* Default gid for reserved blocks */
__le32 s_first_ino; 	 	 /* First non-reserved inode */
__le16 s_inode_size; 		 /* size of inode structure */
__le16 s_block_group_nr; /* block group # of this superblock */
__le32 s_feature_compat; /* compatible feature set */
__le32 s_feature_incompat; /* incompatible feature set */
__le32 s_feature_ro_compat; /* readonly-compatible feature set */
__u8 s_uuid[16];		 /* 128-bit uuid for volume */
char s_volume_name[16]; /* volume name */
char s_last_mounted[64]; /* directory where last mounted */
__le32 s_algorithm_usage_bitmap; /* For compression */
__u8 s_prealloc_blocks; /* Nr of blocks to try to preallocate*/
__u8 s_prealloc_dir_blocks; /* Nr to preallocate for dirs */
__u16 s_padding1;
__u8 s_journal_uuid[16]; /* uuid of journal superblock */
__u32 s_journal_inum;		 /* inode number of journal file */
__u32 s_journal_dev;	 	 /* device number of journal file */
__u32 s_last_orphan;	 	 /* start of list of inodes to delete */
__u32 s_hash_seed[4];		 /* HTREE hash seed */
__u8 s_def_hash_version; /* Default hash version to use */
__u8 s_reserved_char_pad;
__u16 s_reserved_word_pad;
__le32 s_default_mount_opts;
__le32 s_first_meta_bg; /* First metablock block group */
__u32 s_reserved[190]; /* Padding to the end of the block */
};

struct ext2_group_desc
{
__le32 bg_block_bitmap;      /* Blocks bitmap block */
__le32 bg_inode_bitmap;      /* Inodes bitmap block */
__le32 bg_inode_table;       /* Inodes table block */
__le16 bg_free_blocks_count; /* Free blocks count */
__le16 bg_free_inodes_count; /* Free inodes count */
__le16 bg_used_dirs_count; /* Directories count */
__le16 bg_pad;
__le32 bg_reserved[3];
};

struct ext2_inode {
__le16 i_mode;       /* File mode */
__le16 i_uid;        /* Low 16 bits of Owner Uid */
__le32 i_size;       /* Size in bytes */
__le32 i_atime; /* Access time */
__le32 i_ctime; /* Creation time */
__le32 i_mtime; /* Modification time */
__le32 i_dtime; /* Deletion Time */
__le16 i_gid;        /* Low 16 bits of Group Id */
__le16 i_links_count; /* Links count */
__le32 i_blocks; /* Blocks count */
__le32 i_flags; /* File flags */
union {
         struct {
             __le32 l_i_reserved1;
         } linux1;
         struct {
             __le32 h_i_translator;
         } hurd1;
         struct {
             __le32 m_i_reserved1;
         } masix1;
} osd1;              /* OS dependent 1 */
__le32 i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
__le32 i_generation; /* File version (for NFS) */
__le32 i_file_acl; /* File ACL */
__le32 i_dir_acl; /* Directory ACL */
__le32 i_faddr; /* Fragment address */
union {
         struct {
             __u8 l_i_frag; /* Fragment number */
             __u8 l_i_fsize; /* Fragment size */
             __u16 i_pad1;
             __le16 l_i_uid_high; /* these 2 fields */
             __le16 l_i_gid_high; /* were reserved2[0] */
             __u32 l_i_reserved2;
         } linux2;
         struct {
             __u8 h_i_frag; /* Fragment number */
             __u8 h_i_fsize; /* Fragment size */
             __le16 h_i_mode_high;
             __le16 h_i_uid_high;
             __le16 h_i_gid_high;
             __le32 h_i_author;
         } hurd2;
         struct {
             __u8 m_i_frag; /* Fragment number */
             __u8 m_i_fsize; /* Fragment size */
             __u16 m_pad1;
             __u32 m_i_reserved2[2];
         } masix2;
} osd2;              /* OS dependent 2 */
};

int main(int argc, char **argv) {
    int inodeNum = 0;
    struct ext2_super_block super;
    struct ext2_group_desc groupDesc;
    struct ext2_inode inode;
    unsigned char char_buffer[1024];
    FILE *fp;

    if (argc < 3) {
        printf("ERROR: need inode number and disk image name\n");
        return 0;
    }
    //inode number 
    int inodeNum = argv[1];

    // Get file system to read
    fp = fopen(argv[2],"r");
    
    // lseek(fd, 1024, SEEK_SET);
    // read(fd, &super, sizeof(super));
    // block_size = 1024 << super.s_log_block_size; // Get block size

    fseek(fp, 1024, SEEK_SET);
    fread(&super, sizeof(super), 1, fp);

    fseek(fp, 5120, SEEK_SET);
    fread(&groupDesc, sizeof(groupDesc), 1, fp);

    fseek(fp, (128 * (inodeNum - 1)), SEEK_CUR);
    fread(&inode, sizeof(inode), 1 fp);

    fseek(fp, 1024 * (inode.i_block[0]), SEEK_SET);
    fread(char_buffer, 1, 1024, fp);

    printf(char_buffer);

    // Get superblock
    // superblock contains group descriptor
    // GD has blocks that are 1024 bytes large AKA 400 hex
    // --- each block is 400 hex byets
    // Its fifth block contains the location of all of the inodes
    // -- the fifth block at 1400 hex
    // Each inode location is offset by a certain amount within that block (in this case could be 128 bytes
    // To get to inode 1 then 1400 + (80 * (i - 1))

    return 0;
}
