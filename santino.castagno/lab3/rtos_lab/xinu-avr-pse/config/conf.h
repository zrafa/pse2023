/* conf.h (GENERATED FILE; DO NOT EDIT) */

/* Device switch table declarations */

/* Device table entry */
struct	dentry	{
	int32   dvnum;
	int32   dvminor;
	char    dvname[10];
	devcall (*dvinit) (struct dentry *);
	devcall (*dvopen) (struct dentry *, char *, char *);
	devcall (*dvclose)(struct dentry *);
	devcall (*dvread) (struct dentry *, void *, uint32);
	devcall (*dvwrite)(struct dentry *, void *, uint32);
	devcall (*dvseek) (struct dentry *, int32);
	devcall (*dvgetc) (struct dentry *);
	devcall (*dvputc) (struct dentry *, char);
	devcall (*dvcntl) (struct dentry *, int32, int32, int32);
	void    *dvcsr;
	void    (*dvintr)(void);
	byte    dvirq;
};

extern	const __flash struct dentry	devtab[] ; /* one entry per device */

/* Device name definitions */

#define CONSOLE              0	/* type null     */
#define NULLDEV              1	/* type null     */
#define NAMESPACE            2	/* type nam      */

/* Control block sizes */

#define	Nnull	2
#define	Nnam	1

#define NDEVS 3


/* Configuration and Size Constants */

#define	NPROC	     7		/* number of user processes		*/
#define	NSEM	     0		/* number of semaphores			*/
