#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void){
	for(int i=0;i<134;i++){
		fprintf(stderr,"%d\t",i);
		fflush(stderr);
		perror(strerror(i));
	}
    return errno;
}
/*
0	Success: Success
1	Operation not permitted: Success
2	No such file or directory: Success
3	No such process: Success
4	Interrupted system call: Success
5	Input/output error: Success
6	No such device or address: Success
7	Argument list too long: Success
8	Exec format error: Success
9	Bad file descriptor: Success
10	No child processes: Success
11	Resource temporarily unavailable: Success
12	Cannot allocate memory: Success
13	Permission denied: Success
14	Bad address: Success
15	Block device required: Success
16	Device or resource busy: Success
17	File exists: Success
18	Invalid cross-device link: Success
19	No such device: Success
20	Not a directory: Success
21	Is a directory: Success
22	Invalid argument: Success
23	Too many open files in system: Success
24	Too many open files: Success
25	Inappropriate ioctl for device: Success
26	Text file busy: Success
27	File too large: Success
28	No space left on device: Success
29	Illegal seek: Success
30	Read-only file system: Success
31	Too many links: Success
32	Broken pipe: Success
33	Numerical argument out of domain: Success
34	Numerical result out of range: Success
35	Resource deadlock avoided: Success
36	File name too long: Success
37	No locks available: Success
38	Function not implemented: Success
39	Directory not empty: Success
40	Too many levels of symbolic links: Success
41	Unknown error 41: Success
42	No message of desired type: Success
43	Identifier removed: Success
44	Channel number out of range: Success
45	Level 2 not synchronized: Success
46	Level 3 halted: Success
47	Level 3 reset: Success
48	Link number out of range: Success
49	Protocol driver not attached: Success
50	No CSI structure available: Success
51	Level 2 halted: Success
52	Invalid exchange: Success
53	Invalid request descriptor: Success
54	Exchange full: Success
55	No anode: Success
56	Invalid request code: Success
57	Invalid slot: Success
58	Unknown error 58: Success
59	Bad font file format: Success
60	Device not a stream: Success
61	No data available: Success
62	Timer expired: Success
63	Out of streams resources: Success
64	Machine is not on the network: Success
65	Package not installed: Success
66	Object is remote: Success
67	Link has been severed: Success
68	Advertise error: Success
69	Srmount error: Success
70	Communication error on send: Success
71	Protocol error: Success
72	Multihop attempted: Success
73	RFS specific error: Success
74	Bad message: Success
75	Value too large for defined data type: Success
76	Name not unique on network: Success
77	File descriptor in bad state: Success
78	Remote address changed: Success
79	Can not access a needed shared library: Success
80	Accessing a corrupted shared library: Success
81	.lib section in a.out corrupted: Success
82	Attempting to link in too many shared libraries: Success
83	Cannot exec a shared library directly: Success
84	Invalid or incomplete multibyte or wide character: Success
85	Interrupted system call should be restarted: Success
86	Streams pipe error: Success
87	Too many users: Success
88	Socket operation on non-socket: Success
89	Destination address required: Success
90	Message too long: Success
91	Protocol wrong type for socket: Success
92	Protocol not available: Success
93	Protocol not supported: Success
94	Socket type not supported: Success
95	Operation not supported: Success
96	Protocol family not supported: Success
97	Address family not supported by protocol: Success
98	Address already in use: Success
99	Cannot assign requested address: Success
100	Network is down: Success
101	Network is unreachable: Success
102	Network dropped connection on reset: Success
103	Software caused connection abort: Success
104	Connection reset by peer: Success
105	No buffer space available: Success
106	Transport endpoint is already connected: Success
107	Transport endpoint is not connected: Success
108	Cannot send after transport endpoint shutdown: Success
109	Too many references: cannot splice: Success
110	Connection timed out: Success
111	Connection refused: Success
112	Host is down: Success
113	No route to host: Success
114	Operation already in progress: Success
115	Operation now in progress: Success
116	Stale file handle: Success
117	Structure needs cleaning: Success
118	Not a XENIX named type file: Success
119	No XENIX semaphores available: Success
120	Is a named type file: Success
121	Remote I/O error: Success
122	Disk quota exceeded: Success
123	No medium found: Success
124	Wrong medium type: Success
125	Operation canceled: Success
126	Required key not available: Success
127	Key has expired: Success
128	Key has been revoked: Success
129	Key was rejected by service: Success
130	Owner died: Success
131	State not recoverable: Success
132	Operation not possible due to RF-kill: Success
133	Memory page has hardware error: Success
*/
