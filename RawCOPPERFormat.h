1 	//+
2 	// File : RawCOPPERFormat.h
3 	// Description : Module to handle raw data from COPPER
4 	//
5 	// Author : Satoru Yamada, IPNS, KEK
6 	// Date : 2 - Aug - 2013
7 	//-
8 	#ifndef RAWCOPPERFORMAT_H
9 	#define RAWCOPPERFORMAT_H
10
11 	// Includes
12 	#include <stdio.h>
13 	#include <stdlib.h>
14 	#include <sys/time.h>
15
16 	//#include <rawdata/dataobjects/RawDataBlock.h>
17 	#include <rawdata/RawCOPPERPackerInfo.h>
18
19 	#include <framework/datastore/DataStore.h>
20
21
22
23 	#include <TObject.h>
24
25 	//#define USE_B2LFEE_FORMAT_BOTH_VER1_AND_2
26
27 	#define DETECTOR_MASK 0xFF000000 // tentative
28 	#define COPPERID_MASK 0x00FFFFFF // tentative
29 	#define SVD_ID  0x01000000 // tentative
30 	#define CDC_ID  0x02000000 // tentative
31 	#define TOP_ID 0x03000000 // tentative
32 	#define ARICH_ID 0x04000000 // tentative
33 	#define BECL_ID  0x05000000 // tentative
34 	#define EECL_ID  0x06000000 // tentative
35 	#define BKLM_ID  0x07000000 // tentative
36 	#define EKLM_ID  0x08000000 // tentative
37 	#define TRGDATA_ID  0x10000000 // tentative
38 	#define CDCTRGDATA_ID  0x11000000 // tentative
39 	#define ECLTRGDATA_ID  0x12000000 // tentative
40 	#define TOPTRGDATA_ID  0x13000000 // tentative
41 	#define KLMTRGDATA_ID  0x14000000 // tentative
42 	#define GDLTRGDATA_ID  0x15000000 // tentative
43
44
45 	namespace Belle2 {
46
47 	  /**
48 	   * The Raw COPPER class
49 	   * This class stores data received by COPPER via belle2linkt
50 	   * Data from all detectors except PXD are stored in this class
51 	   */
52 	  class RawCOPPERFormat : public TObject {
53 	  public:
54 	    /*     //! Default constructor */
55 	    RawCOPPERFormat();
56
57 	    //! Constructor using existing pointer to raw data buffer
58 	    //RawCOPPERFormat(int* bufin, int nwords);
59 	    //! Destructor
60 	    virtual ~RawCOPPERFormat() {}
61
62 	    //
63 	    // Functions for  RawDataBlock
64 	    //
65 	    //! set buffer ( delete_flag : m_buffer is freeed( = 0 )/ not freeed( = 1 ) in Destructer )
66 	    void SetBuffer(int* bufin, int nwords, int delete_flag, int num_events, int num_nodes);
67
68 	    //! Get total length of m_buffer
69 	    virtual int TotalBufNwords();
70
71 	    //! get nth buffer pointer
72 	    virtual int* GetBuffer(int n);
73
74 	    //! get pointer to  buffer(m_buffer)
75 	    virtual int* GetWholeBuffer();
76
77 	    //! get # of data blocks = (# of nodes)*(# of events)
78 	    virtual int GetNumEntries() { return m_num_events * m_num_nodes; }
79
80 	    //! get # of data sources(e.g. # of COPPER boards) in m_buffer
81 	    virtual int GetNumNodes() { return m_num_nodes; }
82
83 	    //! get # of events in m_buffer
84 	    virtual int GetNumEvents() { return m_num_events; }
85
86 	    //! get size of a data block
87 	    virtual int GetBlockNwords(int n);
88
89 	    //! print out data
90 	    virtual void PrintData(int* buf, int nwords);
91
92 	    enum {
93 	      POS_NWORDS = 0,
94 	      POS_NODE_ID = 6
95 	    };
96
97 	    enum {
98 	      // Tentatively needed to distinguish new and old FTSW format, which will be changed in Nov. 2013
99 	      POS_FTSW_ID_OLD = 5,
100 	      TEMP_POS_NWORDS_HEADER = 1,
101 	      OLD_FTSW_NWORDS_HEADER = 6
102 	    };
103
104 	    //
105 	    // Functions for RawCOPPER
106 	    //
107
108 	    // POINTER TO "DETECTOR BUFFER"
109 	    //( after removing "B2link headers" from "FINESSE buffer". THIS IS THE RAW DATA FROM A DETECTOR
110
111 	    //! get Detector buffer length
112 	    virtual int GetDetectorNwords(int n, int finesse_num) = 0;
113
114 	    //! get Detector buffer length of slot A
115 	    virtual int Get1stDetectorNwords(int n) = 0;
116
117 	    //! get Detector buffer length of slot B
118 	    virtual int Get2ndDetectorNwords(int n) = 0;
119
120 	    //! get Detector buffer length of slot C
121 	    virtual int Get3rdDetectorNwords(int n) = 0;
122
123 	    //! get Detector buffer length of slot D
124 	    virtual int Get4thDetectorNwords(int n) = 0;
125
126 	    //! get Detector buffer
127 	    virtual int* GetDetectorBuffer(int n, int finesse_num);
128
129 	    //! get Detector buffer of slot A
130 	    virtual int* Get1stDetectorBuffer(int n) = 0;
131
132 	    //! get Detector Buffer of slot B
133 	    virtual int* Get2ndDetectorBuffer(int n) = 0;
134
135 	    //! get Detector Buffer of slot C
136 	    virtual int* Get3rdDetectorBuffer(int n) = 0;
137
138 	    //! get Detector Buffer of slot D
139 	    virtual int* Get4thDetectorBuffer(int n) = 0;
140 	    ///////////////////////////////////////////////////////////////////////////////////////
141
142 	    //! get posistion of COPPER block in unit of word
143 	    virtual int GetBufferPos(int n) = 0;
144
145 	    //! get buffer pointer of rawcopper header(Currently same as GetBufferPos)
146 	    virtual int* GetRawHdrBufPtr(int n);
147
148 	    //! get buffer pointer of rawcopper trailer
149 	    virtual int* GetRawTrlBufPtr(int n) = 0;
150
151 	    //! get FINESSE buffer pointer
152 	    virtual int* GetFINESSEBuffer(int n, int finesse_num);
153
154 	    //! get FINESSE buffer pointer for slot A
155 	    virtual int* Get1stFINESSEBuffer(int n);
156
157 	    //! get FINESSE buffer pointer for slot B
158 	    virtual int* Get2ndFINESSEBuffer(int n);
159
160 	    //! get FINESSE buffer pointer for slot C
161 	    virtual int* Get3rdFINESSEBuffer(int n);
162
163 	    //! get FINESSE buffer pointer for slot D
164 	    virtual int* Get4thFINESSEBuffer(int n);
165
166
167
168 	    //
169 	    // Get information from "RawCOPPERFormat header" attached by DAQ software
170 	    //
171
172 	    /// get Experimental # from header
173 	    virtual int GetExpNo(int n) = 0;    //! get Experimental # from header
174
175 	    virtual unsigned int GetExpRunSubrun(int n) = 0;    //! Exp# (10bit) run# (14bit) restart # (8bit)
176
177 	    virtual int GetRunNo(int n) = 0;    //! get run # (14bit)
178
179 	    virtual int GetSubRunNo(int n) = 0;    //! get subrun #(8bit)
180
181 	    virtual unsigned int GetEveNo(int n) = 0;    //! get contents of header
182
183 	    virtual int GetDataType(int n) = 0;    //! get contents of header
184
185 	    virtual int GetTruncMask(int n) = 0;    //! get contents of header
186
187 	    //! Get Detected Error bitflag
188 	    virtual unsigned int GetErrorBitFlag(int n) = 0;
189
190 	    //! Add Detected Error bitflag
191 	    virtual void AddErrorBitFlag(int n, unsigned int error_bit_flag) = 0;
192
193 	    //! get node-ID from data
194 	    virtual unsigned int GetNodeID(int n) = 0;
195
196 	    //
197 	    // Get information from 13words "COPPER header" attached by COPPER board
198 	    //
199 	    //! get COPPER counter(not event number)
200 	    virtual unsigned int GetCOPPERCounter(int n) = 0;
201
202 	    //! get # of FINNESEs which contains data
203 	    virtual int GetNumFINESSEBlock(int n) = 0;
204
205 	    //! get # of offset words
206 	    virtual int GetOffsetFINESSE(int n, int finesse);
207
208 	    //! get # of offset words for FINESSE slot A buffer position
209 	    virtual int GetOffset1stFINESSE(int n) = 0;
210
211 	    //! get # of offset words for FINESSE slot B buffer position
212 	    virtual int GetOffset2ndFINESSE(int n);
213
214 	    //! get # of offset words for FINESSE slot C buffer position
215 	    virtual int GetOffset3rdFINESSE(int n);
216
217 	    //! get # of offset words for FINESSE slot D buffer position
218 	    virtual int GetOffset4thFINESSE(int n);
219
220 	    //! get data size of  FINESSE buffer
221 	    virtual int GetFINESSENwords(int n, int finesse) = 0;
222
223 	    //! get data size of  FINESSE slot A buffer
224 	    virtual int Get1stFINESSENwords(int n) = 0;
225
226 	    //! get data size of  FINESSE slot B buffer
227 	    virtual int Get2ndFINESSENwords(int n) = 0;
228
229 	    //! get data size of  FINESSE slot C buffer
230 	    virtual int Get3rdFINESSENwords(int n) = 0;
231
232 	    //! get data size of  FINESSE slot D buffer
233 	    virtual int Get4thFINESSENwords(int n) = 0;
234
235 	    //! For copying FTSW word1 (FEE header)
236 	    virtual unsigned int GetB2LHeaderWord(int n, int finesse_buffer_pos);
237
238 	    //
239 	    // Get information from "B2link(attached by FEE and HLSB) header"
240 	    //
241 	    //! get b2l block from "FEE b2link header"
242 	    //    virtual int* GetFTSW2Words(int n) = 0;
243
244 	    //! get b2l block from "FEE b2link header"
245 	    virtual int* GetExpRunSubrunBuf(int n) = 0;
246
247 	    //! get b2l block from "FEE b2link header"
248 	    virtual unsigned int GetB2LFEE32bitEventNumber(int n) = 0;
249
250 	    //! get Event unixtime from "FEE b2link header"
251 	    virtual double GetEventUnixTime(int n) = 0;
252
253 	    //
254 	    // read magic word to check data
255 	    //
256 	    //! get magic word of  COPPER driver header
257 	    virtual unsigned int GetMagicDriverHeader(int n) = 0;
258
259 	    //! get magic word of  COPPER FPGA header
260 	    virtual unsigned int GetMagicFPGAHeader(int n) = 0;
261
262 	    //! get magic word of  COPPER FPGA trailer
263 	    virtual unsigned int GetMagicFPGATrailer(int n) = 0;
264
265 	    //! get magic word of  COPPER driver trailer
266 	    virtual unsigned int GetMagicDriverTrailer(int n) = 0;
267
268 	    //! Get checksum in RawTrailer
269 	    virtual unsigned int GetTrailerChksum(int  n) = 0 ;
270
271 	    //! Check if COPPER Magic words are correct
272 	    virtual bool CheckCOPPERMagic(int n) = 0;
273
274 	#ifdef USE_B2LFEE_FORMAT_BOTH_VER1_AND_2
275 	    //! Check B2LFEE header version
276 	    virtual void CheckB2LFEEHeaderVersion(int  n) = 0;
277 	#endif
278
279 	    //! Check if COPPER Magic words are correct
280 	    virtual unsigned int GetTTCtimeTRGType(int n) = 0;
281
282 	    //! Check if COPPER Magic words are correct
283 	    virtual unsigned int GetTTUtime(int n) = 0;
284
285 	    //! should be called by DeSerializerCOPPER.cc and fill contents in RawHeader
286 	    virtual unsigned int FillTopBlockRawHeader(unsigned int m_node_id, unsigned int m_data_type, unsigned int m_trunc_mask,
287 	                                               unsigned int prev_eve32, unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no) = 0;
288
289 	    //! read COPPER driver's checksum value
290 	    virtual unsigned int GetDriverChkSum(int n) = 0;
291
292 	    //! calc COPPER driver's checksum value
293 	    virtual unsigned int CalcDriverChkSum(int n) = 0;
294
295
296 	    //! check data contents
297 	    virtual void CheckData(int n,
298 	                           unsigned int prev_evenum, unsigned int* cur_evenum,
299 	                           unsigned int prev_copper_ctr, unsigned int* cur_copper_ctr,
300 	                           unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no) = 0;
301
302 	    //! check data contents
303 	    virtual void CheckUtimeCtimeTRGType(int n) = 0;
304
305 	    //! Get ctime
306 	    virtual int GetTTCtime(int n) = 0;
307
308 	    //! Get trgtype
309 	    virtual int GetTRGType(int n) = 0;
310
311 	    //! Get timeval
312 	    virtual void GetTTTimeVal(int n, struct timeval* tv) = 0;
313
314 	    //! calc XOR checksum
315 	    virtual unsigned int CalcXORChecksum(int* buf, int nwords);
316
317 	    //! Pack data (format ver. = -1 -> Select the latest format version)
318 	    virtual int* PackDetectorBuf(int* packed_buf_nwords,
319 	                                 int* detector_buf_1st, int nwords_1st,
320 	                                 int* detector_buf_2nd, int nwords_2nd,
321 	                                 int* detector_buf_3rd, int nwords_3rd,
322 	                                 int* detector_buf_4th, int nwords_4th,
323 	                                 RawCOPPERPackerInfo rawcprpacker_info) = 0;
324
325 	  protected :
326
327 	    /// number of words of buffer
328 	    int m_nwords;
329
330 	    /// number of nodes in this object
331 	    int m_num_nodes;
332
333 	    /// number of events in this object
334 	    int m_num_events;
335
336 	    /// Buffer to access data
337 	    int* m_buffer; //! not recorded
338
339 	    ///ver.3 : Separate from RawDataBLock to avoid a memory leak ( July 24, 2014)
340 	    ClassDef(RawCOPPERFormat, 3);
341
342 	  };
343
344
345
346 	  inline int* RawCOPPERFormat::GetRawHdrBufPtr(int n)
347 	  {
348 	    int pos_nwords = GetBufferPos(n);
349 	    return &(m_buffer[ pos_nwords ]);
350 	  }
351
352
353 	  inline int RawCOPPERFormat::GetOffset2ndFINESSE(int n)
354 	  {
355 	    return GetOffset1stFINESSE(n) + Get1stFINESSENwords(n);
356 	  }
357
358 	  inline int RawCOPPERFormat::GetOffset3rdFINESSE(int n)
359 	  {
360 	    return GetOffset2ndFINESSE(n) + Get2ndFINESSENwords(n);
361 	  }
362
363 	  inline int RawCOPPERFormat::GetOffset4thFINESSE(int n)
364 	  {
365 	    return GetOffset3rdFINESSE(n) + Get3rdFINESSENwords(n);
366 	  }
367
368
369
370 	  inline int* RawCOPPERFormat::Get1stFINESSEBuffer(int n)
371 	  {
372 	    int pos_nwords = GetOffset1stFINESSE(n);
373 	    if (pos_nwords >= m_nwords) {
374 	      printf("[DEBUG] Data size is smaller than data position info. Exting...\n");
375 	      exit(1);
376 	    }
377 	    return &(m_buffer[ pos_nwords]);
378 	  }
379
380 	  inline int* RawCOPPERFormat::Get2ndFINESSEBuffer(int n)
381 	  {
382 	    int pos_nwords = GetOffset2ndFINESSE(n);
383 	    if (pos_nwords >= m_nwords) {
384 	      printf("[DEBUG] Data size is smaller than data position info. Exting...\n");
385 	      exit(1);
386 	    }
387 	    return &(m_buffer[ pos_nwords]);
388 	  }
389
390 	  inline int* RawCOPPERFormat::Get3rdFINESSEBuffer(int n)
391 	  {
392 	    int pos_nwords = GetOffset3rdFINESSE(n);
393 	    if (pos_nwords >= m_nwords) {
394 	      printf("[DEBUG] Data size is smaller than data position info. Exting...\n");
395 	      exit(1);
396 	    }
397 	    return &(m_buffer[ pos_nwords]);
398 	  }
399
400 	  inline int* RawCOPPERFormat::Get4thFINESSEBuffer(int n)
401 	  {
402 	    int pos_nwords = GetOffset4thFINESSE(n);
403 	    if (pos_nwords >= m_nwords) {
404 	      printf("[DEBUG] Data size is smaller than data position info. Exting...\n");
405 	      exit(1);
406 	    }
407 	    return &(m_buffer[ pos_nwords]);
408 	  }
409
410
411 	}
412
413 	#endif
