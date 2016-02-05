1 	//+
2 	// File : RawCOPPERFormat.cc
3 	// Description : Module to handle raw data from COPPER.
4 	//
5 	// Author : Satoru Yamada, IPNS, KEK
6 	// Date : 3 - July - 2014
7 	//-
8
9 	#include <rawdata/dataobjects/RawCOPPERFormat.h>
10
11
12 	using namespace std;
13 	using namespace Belle2;
14
15
16 	ClassImp(RawCOPPERFormat);
17
18
19 	RawCOPPERFormat::RawCOPPERFormat()
20 	{
21 	  m_nwords = 0;
22 	  m_num_nodes = 0;
23 	  m_num_events = 0;
24 	  m_buffer = NULL;
25
26 	}
27
28
29 	//
30 	// Functions for RawDataBlock
31 	//
32
33
34 	void RawCOPPERFormat::PrintData(int* buf, int nwords)
35 	{
36 	  printf("[DEBUG] ");
37 	  for (int i = 0; i < nwords; i++) {
38 	    printf("%.8x ", buf[ i ]);
39 	    if (i % 10 == 9) printf("\n[DEBUG] ");
40 	  }
41 	  printf("\n[DEBUG] ");
42 	  printf("\n");
43 	  return;
44 	}
45
46
47 	int RawCOPPERFormat::TotalBufNwords()
48 	{
49 	  return m_nwords;
50 	}
51
52
53 	int RawCOPPERFormat::GetBlockNwords(int n)
54 	{
55 	  int size;
56 	  if (n == (m_num_events * m_num_nodes) - 1) {
57 	    size =  m_nwords - GetBufferPos(n);
58 	  } else {
59 	    size = GetBufferPos(n + 1) - GetBufferPos(n);
60 	  }
61 	  return size;
62 	}
63
64
65 	int* RawCOPPERFormat::GetWholeBuffer()
66 	{
67 	  return m_buffer;
68 	}
69
70 	int* RawCOPPERFormat::GetBuffer(int n)
71 	{
72 	  int pos_nwords = GetBufferPos(n);
73 	  return &(m_buffer[ pos_nwords ]);
74 	}
75
76
77
78
79 	void RawCOPPERFormat::SetBuffer(int* bufin, int nwords, int delete_flag, int num_events, int num_nodes)
80 	{
81 	  if (delete_flag  == 1) {
82 	    printf("RawCOPPER format class does not delete m_buffer. Please specify 0 for delete_flag. Exiting...\n");
83 	    exit(1);
84 	  }
85
86 	  if (bufin == NULL) {
87 	    printf("[DEBUG] bufin is NULL. Exting...\n");
88 	    exit(1);
89 	  }
90
91 	//   if (!m_use_prealloc_buf && m_buffer != NULL) delete[] m_buffer;
92 	//   if (delete_flag == 0) {
93 	//     m_use_prealloc_buf = true;
94 	//   } else {
95 	//     m_use_prealloc_buf = false;
96 	//   }
97
98 	  m_nwords = nwords;
99 	  m_buffer = bufin;
100
101 	  m_num_nodes = num_nodes;
102 	  m_num_events = num_events;
103
104 	  // Set length at the first word of the buffer
105
106 	  //
107 	  // Assign header and trailer
108 	  //
109
110 	}
111
112
113
114 	unsigned int  RawCOPPERFormat::CalcXORChecksum(int* buf, int nwords)
115 	{
116 	  unsigned int checksum = 0;
117 	  for (int i = 0; i < nwords; i++) {
118 	    checksum = checksum ^ buf[ i ];
119 	  }
120 	  return checksum;
121 	}
122
123
124
125
126 	int RawCOPPERFormat::GetOffsetFINESSE(int n, int finesse_num)
127 	{
128 	  switch (finesse_num) {
129 	    case 0 :
130 	      return GetOffset1stFINESSE(n);
131 	      break;
132 	    case 1 :
133 	      return GetOffset2ndFINESSE(n);
134 	      break;
135 	    case 2 :
136 	      return GetOffset3rdFINESSE(n);
137 	      break;
138 	    case 3 :
139 	      return GetOffset4thFINESSE(n);
140 	      break;
141 	    default :
142 	      break;
143 	  }
144
145 	  char err_buf[500];
146 	  sprintf(err_buf, "Specifined FINESSE number( = %d ) is invalid. Exiting...\n%s %s %d\n", finesse_num,
147 	          __FILE__, __PRETTY_FUNCTION__, __LINE__);
148 	  string err_str = err_buf; throw (err_str);
149 	  //   sleep(12345678);
150 	  //   exit(-1);
151 	  //   return 0;
152
153 	}
154
155
156
157
158 	int* RawCOPPERFormat::GetFINESSEBuffer(int n, int finesse_num)
159 	{
160 	  switch (finesse_num) {
161 	    case 0 :
162 	      return Get1stFINESSEBuffer(n);
163 	      break;
164 	    case 1 :
165 	      return Get2ndFINESSEBuffer(n);
166 	      break;
167 	    case 2 :
168 	      return Get3rdFINESSEBuffer(n);
169 	      break;
170 	    case 3 :
171 	      return Get4thFINESSEBuffer(n);
172 	      break;
173 	    default :
174 	      break;
175 	  }
176
177 	  char err_buf[500];
178 	  sprintf(err_buf, "Specifined FINESSE number( = %d ) is invalid. Exiting...\n%s %s %d\n", finesse_num,
179 	          __FILE__, __PRETTY_FUNCTION__, __LINE__);
180 	  string err_str = err_buf; throw (err_str);
181 	//   sleep(12345678);
182 	//   exit(-1);
183 	//   return 0;
184 	}
185
186
187
188
189 	int* RawCOPPERFormat::GetDetectorBuffer(int n, int finesse_num)
190 	{
191 	  switch (finesse_num) {
192 	    case 0 :
193 	      return Get1stDetectorBuffer(n);
194 	      break;
195 	    case 1 :
196 	      return Get2ndDetectorBuffer(n);
197 	      break;
198 	    case 2 :
199 	      return Get3rdDetectorBuffer(n);
200 	      break;
201 	    case 3 :
202 	      return Get4thDetectorBuffer(n);
203 	      break;
204 	    default :
205 	      break;
206 	  }
207
208 	  char err_buf[500];
209 	  sprintf(err_buf, "Specifined FINESSE number( = %d ) is invalid. Exiting...\n%s %s %d\n", finesse_num,
210 	          __FILE__, __PRETTY_FUNCTION__, __LINE__);
211 	  string err_str = err_buf; throw (err_str);
212 	//   sleep(12345678);
213 	//   exit(-1);
214 	//   return 0;
215 	}
216
217
218
219 	unsigned int RawCOPPERFormat::GetB2LHeaderWord(int n, int finesse_buffer_pos)
220 	{
221 	  unsigned int word[4];
222 	  unsigned int ret_word = 0;
223 	  int flag = 0, err_flag = 0;
224
225 	  for (int i = 0; i < 4; i++) {
226 	    if (GetFINESSENwords(n, i) > 0) {
227 	      word[ i ] = m_buffer[ GetOffsetFINESSE(n, i) + finesse_buffer_pos ];
228 	      if (flag != 0 && (ret_word != word[ i ])) {
229 	        err_flag = 1;
230 	      }
231 	      ret_word = word[ i ];
232 	      flag = 1;
233 	    }
234 	  }
235
236
237 	  if (flag == 0) {
238 	    char err_buf[500];
239 	    sprintf(err_buf, "No HSLB data in COPPER data. Exiting...\n %s %s %d\n",
240 	            __FILE__, __PRETTY_FUNCTION__, __LINE__);
241 	    string err_str = err_buf; throw (err_str);
242 	//     sleep(12345678);
243 	//     exit(-1);
244 	  }
245
246
247 	  if (err_flag == 1) {
248
249 	    char err_buf[500];
250 	    sprintf(err_buf, "CORRUPTED DATA: Different event number over HSLBs : slot A 0x%x : B 0x%x :C 0x%x : D 0x%x\n %s %s %d\n",
251 	            word[ 0 ], word[ 1 ], word[ 2 ], word[ 3 ],
252 	            __FILE__, __PRETTY_FUNCTION__, __LINE__);
253 	    printf("[DEBUG] [ERROR] %s\n", err_buf);
254 	#ifndef NO_DATA_CHECK
255 	    string err_str = err_buf; throw (err_str);
256
257 	//     sleep(12345678);
258 	//     exit(-1);
259 	#endif
260 	  }
261
262 	  return ret_word;
263
264 	}
