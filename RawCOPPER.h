//+
2 	// File : RawCOPPER.h
3 	// Description : Module to handle raw data from COPPER
4 	//
5 	// Author : Satoru Yamada, IPNS, KEK
6 	// Date : 2 - Aug - 2013
7 	//-
8
9 	#ifndef RAWCOPPER_H
10 	#define RAWCOPPER_H
11
12 	// Includes
13 	#include <stdio.h>
14 	#include <stdlib.h>
15 	#include <string.h>
16 	#include <sys/time.h>
17
18 	#include <rawdata/dataobjects/RawDataBlock.h>
19 	#include <rawdata/dataobjects/RawCOPPERFormat.h>
20 	#include <rawdata/dataobjects/RawCOPPERFormat_latest.h>
21 	#include <rawdata/dataobjects/RawCOPPERFormat_v0.h>
22 	#include <rawdata/dataobjects/RawCOPPERFormat_v1.h>
23 	#include <rawdata/dataobjects/PreRawCOPPERFormat_v1.h>
24 	#include <rawdata/dataobjects/PreRawCOPPERFormat_latest.h>
25 	#include <framework/datastore/DataStore.h>
26 	#include <rawdata/RawCOPPERPackerInfo.h>
27
28
29 	#include <TObject.h>
30
31 	//#define USE_B2LFEE_FORMAT_BOTH_VER1_AND_2
32
33
34 	using namespace std;
35
36 	// Divide ECL and KLM to barrel and endcap categories from Itoh-san's suggestion
37 	// Updated on May 9, 2014
38
39 	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
40 	//
41 	// The latest DAQformat version number
42 	#define LATEST_POSTREDUCTION_FORMAT_VER 2 // Since Apr. 21, 2015
43 	//
44 	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
45
46
47 	namespace Belle2 {
48
49 	  /**
50 	   * The Raw COPPER class
51 	   * This class stores data received by COPPER via belle2linkt
52 	   * Data from all detectors except PXD are stored in this class
53 	   */
54 	  class RawCOPPER : public RawDataBlock {
55 	  public:
56 	    //! Default constructor
57 	    RawCOPPER();
58
59 	    //! Constructor using existing pointer to raw data buffer
60 	    //RawCOPPER(int* bufin, int nwords);
61 	    //! Destructor
62 	    virtual ~RawCOPPER();
63
64 	    //
65 	    // Get position of or pointer to data
66 	    //
67
68 	    //! set buffer ( delete_flag : m_buffer is freeed( = 0 )/ not freeed( = 1 ) in Destructer )
69 	    void SetBuffer(int* bufin, int nwords, int delete_flag, int num_events, int num_nodes);
70
71 	    ///////////////////////////////////////////////////////////////////////////////////////
72 	    // POINTER TO "DETECTOR BUFFER"
73 	    //( after removing "B2link headers" from "FINESSE buffer". THIS IS THE RAW DATA FROM A DETECTOR
74 	    ///////////////////////////////////////////////////////////////////////////////////////
75 	    //! get Detector buffer length
76 	    int GetDetectorNwords(int n, int finesse_num);
77
78 	    //! get Detector buffer length of slot A
79 	    int Get1stDetectorNwords(int n);
80
81 	    //! get Detector buffer length of slot B
82 	    int Get2ndDetectorNwords(int n);
83
84 	    //! get Detector buffer length of slot C
85 	    int Get3rdDetectorNwords(int n);
86
87 	    //! get Detector buffer length of slot D
88 	    int Get4thDetectorNwords(int n);
89
90 	    //! get Detector buffer
91 	    int* GetDetectorBuffer(int n, int finesse_num);
92
93 	    //! get Detector buffer of slot A
94 	    int* Get1stDetectorBuffer(int n);
95
96 	    //! get Detector Buffer of slot B
97 	    int* Get2ndDetectorBuffer(int n);
98
99 	    //! get Detector Buffer of slot C
100 	    int* Get3rdDetectorBuffer(int n);
101
102 	    //! get Detector Buffer of slot D
103 	    int* Get4thDetectorBuffer(int n);
104 	    ///////////////////////////////////////////////////////////////////////////////////////
105
106 	    //! get posistion of COPPER block in unit of word
107 	    virtual int GetBufferPos(int n);
108
109 	    //! get buffer pointer of rawcopper header(Currently same as GetBufferPos)
110 	    virtual int* GetRawHdrBufPtr(int n);
111
112 	    //! get buffer pointer of rawcopper trailer
113 	    virtual int* GetRawTrlBufPtr(int n);
114
115 	    //! get FINESSE buffer pointer
116 	    int* GetFINESSEBuffer(int n, int finesse_num);
117
118 	    //! get FINESSE buffer pointer for slot A
119 	    int* Get1stFINESSEBuffer(int n);
120
121 	    //! get FINESSE buffer pointer for slot B
122 	    int* Get2ndFINESSEBuffer(int n);
123
124 	    //! get FINESSE buffer pointer for slot C
125 	    int* Get3rdFINESSEBuffer(int n);
126
127 	    //! get FINESSE buffer pointer for slot D
128 	    int* Get4thFINESSEBuffer(int n);
129
130
131 	    //
132 	    // Get information from "RawCOPPER header" attached by DAQ software
133 	    //
134
135 	    //! get Experimental # from header
136 	    int GetExpNo(int n);    //! get Experimental # from header
137
138 	    unsigned int GetExpRunSubrun(int n);    //! Exp# (10bit) run# (14bit) restart # (8bit)
139
140 	    int GetRunNo(int n);    //! get run # (14bit)
141
142 	    int GetSubRunNo(int n);    //! get subrun #(8bit)
143
144 	    unsigned int GetEveNo(int n);    //! get contents of header
145
146 	    int GetDataType(int n);    //! get contents of header
147
148 	    int GetTruncMask(int n);    //! get contents of header
149
150 	    //! Get Detected Error bitflag
151 	    unsigned int GetErrorBitFlag(int n);
152
153 	    //! Get Detected Error bitflag
154 	    void AddErrorBitFlag(int n, unsigned int error_bit_flag);
155
156 	    //! get node-ID from data
157 	    unsigned int GetNodeID(int n);
158
159 	    //
160 	    // Get information from 13words "COPPER header" attached by COPPER board
161 	    //
162 	    //! get COPPER counter(not event number)
163 	    virtual unsigned int GetCOPPERCounter(int n);
164
165 	    //! get # of FINNESEs which contains data
166 	    virtual int GetNumFINESSEBlock(int n);
167
168 	    //! get # of offset words
169 	    int GetOffsetFINESSE(int n, int finesse);
170
171 	    //! get # of offset words for FINESSE slot A buffer position
172 	    int GetOffset1stFINESSE(int n);
173
174 	    //! get # of offset words for FINESSE slot B buffer position
175 	    int GetOffset2ndFINESSE(int n);
176
177 	    //! get # of offset words for FINESSE slot C buffer position
178 	    int GetOffset3rdFINESSE(int n);
179
180 	    //! get # of offset words for FINESSE slot D buffer position
181 	    int GetOffset4thFINESSE(int n);
182
183 	    //! get data size of  FINESSE buffer
184 	    int GetFINESSENwords(int n, int finesse);
185
186 	    //! get data size of  FINESSE slot A buffer
187 	    int Get1stFINESSENwords(int n);
188
189 	    //! get data size of  FINESSE slot B buffer
190 	    int Get2ndFINESSENwords(int n);
191
192 	    //! get data size of  FINESSE slot C buffer
193 	    int Get3rdFINESSENwords(int n);
194
195 	    //! get data size of  FINESSE slot D buffer
196 	    int Get4thFINESSENwords(int n);
197
198 	    //! For copying FTSW word1 (FEE header)
199 	    unsigned int GetB2LHeaderWord(int n, int finesse_buffer_pos);
200
201 	    //
202 	    // Get information from "B2link(attached by FEE and HLSB) header"
203 	    //
204 	    //! get b2l block from "FEE b2link header"
205 	    //    virtual int* GetFTSW2Words(int n);
206
207 	    //! get b2l block from "FEE b2link header"
208 	    virtual int* GetExpRunSubrunBuf(int n);
209
210 	    //! get b2l block from "FEE b2link header"
211 	    virtual unsigned int GetB2LFEE32bitEventNumber(int n);
212
213 	    //! get Event unixtime from "FEE b2link header"
214 	    double GetEventUnixTime(int n);
215
216 	    //
217 	    // read magic word to check data
218 	    //
219 	    //! get magic word of  COPPER driver header
220 	    unsigned int GetMagicDriverHeader(int n);
221
222 	    //! get magic word of  COPPER FPGA header
223 	    unsigned int GetMagicFPGAHeader(int n);
224
225 	    //! get magic word of  COPPER FPGA trailer
226 	    unsigned int GetMagicFPGATrailer(int n);
227
228 	    //! get magic word of  COPPER driver trailer
229 	    unsigned int GetMagicDriverTrailer(int n);
230
231 	    //! Get checksum in RawTrailer
232 	    unsigned int GetTrailerChksum(int  n);
233
234 	    //! Check if COPPER Magic words are correct
235 	    bool CheckCOPPERMagic(int n);
236
237 	#ifdef USE_B2LFEE_FORMAT_BOTH_VER1_AND_2
238 	    //! Check B2LFEE header version
239 	    void CheckB2LFEEHeaderVersion(int  n);
240 	#endif
241
242 	    //! Check if COPPER Magic words are correct
243 	    unsigned int GetTTCtimeTRGType(int n);
244
245 	    //! Check if COPPER Magic words are correct
246 	    unsigned int GetTTUtime(int n);
247
248 	    //! should be called by DeSerializerCOPPER.cc and fill contents in RawHeader
249 	    unsigned int FillTopBlockRawHeader(unsigned int m_node_id, unsigned int m_data_type, unsigned int m_trunc_mask,
250 	                                       unsigned int prev_eve32, unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no);
251
252 	    //! read COPPER driver's checksum value
253 	    unsigned int GetDriverChkSum(int n);
254
255 	    //! calc COPPER driver's checksum value
256 	    unsigned int CalcDriverChkSum(int n);
257
258 	    //! calc XOR checksum
259 	    unsigned int CalcXORChecksum(int* buf, int nwords);
260
261 	    //! check data contents
262 	    void CheckData(int n,
263 	                   unsigned int prev_evenum, unsigned int* cur_evenum,
264 	                   unsigned int prev_copper_ctr, unsigned int* cur_copper_ctr,
265 	                   unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no);
266
267 	    //! check data contents
268 	    void CheckUtimeCtimeTRGType(int n);
269
270 	    //! Get ctime
271 	    int GetTTCtime(int n);
272
273 	    //! Get trgtype
274 	    int GetTRGType(int n);
275
276 	    //! Get timeval
277 	    void GetTTTimeVal(int n, struct timeval* tv);
278
279 	    //! read data, detect and set the version number of the data format
280 	    void SetVersion();
281
282 	    //! Get timeval
283 	    void SetVersion(string class_name);
284
285 	    //! Check the version number of data format
286 	    void CheckVersionSetBuffer();
287
288 	    //! show m_buffer
289 	    void ShowBuffer();
290
291 	    //! Packer for RawCOPPER class
292 	    //! Pack data (format ver. = -1 -> Select the latest format version)
293 	    void PackDetectorBuf(int* detector_buf_1st, int nwords_1st,
294 	                         int* detector_buf_2nd, int nwords_2nd,
295 	                         int* detector_buf_3rd, int nwords_3rd,
296 	                         int* detector_buf_4th, int nwords_4th,
297 	                         RawCOPPERPackerInfo rawcprpacker_info);
298
299 	    //! Pack dummy data (format ver. = -1 -> Select the latest format version)
300 	    void PackDetectorBuf4DummyData(int* detector_buf_1st, int nwords_1st,
301 	                                   int* detector_buf_2nd, int nwords_2nd,
302 	                                   int* detector_buf_3rd, int nwords_3rd,
303 	                                   int* detector_buf_4th, int nwords_4th,
304 	                                   RawCOPPERPackerInfo rawcprpacker_info);
305
306 	    enum {
307 	      POS_FORMAT_VERSION = 1,
308 	      FORMAT_MASK = 0x0000FF00
309 	    };
310
311 	    //! class to access
312 	    RawCOPPERFormat* m_access; //! do not record
313
314 	    /// Version of the format
315 	    int m_version; //! do not record
316
317 	  protected :
318 	    ///ver.2 Change FEE format as presented at B2GM in Nov.2013 ( Nov.20, 2013)
319 	    ///ver.3 Change FEE format as presented at B2GM in Nov.2013 ( May 1, 2014)
320 	    ///ver.4 Do not record m_access pointer ( Dec 19, 2014)
321 	    ClassDef(RawCOPPER, 3);
322
323 	  };
324
325
326 	  inline int* RawCOPPER::GetRawHdrBufPtr(int n)
327 	  {
328 	    CheckVersionSetBuffer();
329 	    return m_access->GetRawHdrBufPtr(n);
330 	  }
331
332 	  inline int* RawCOPPER::GetRawTrlBufPtr(int n)
333 	  {
334 	    CheckVersionSetBuffer();
335 	    return m_access->GetRawTrlBufPtr(n);
336 	  }
337
338 	  inline unsigned int RawCOPPER::GetDriverChkSum(int n)
339 	  {
340 	    CheckVersionSetBuffer();
341 	    return m_access->GetDriverChkSum(n);
342 	  }
343
344 	  inline int RawCOPPER::GetExpNo(int n)
345 	  {
346 	    CheckVersionSetBuffer();
347 	    return m_access->GetExpNo(n);
348 	  }
349
350 	  inline unsigned int RawCOPPER::GetExpRunSubrun(int n)
351 	  {
352 	    CheckVersionSetBuffer();
353 	    return m_access->GetExpRunSubrun(n);
354 	  }
355
356 	  inline int RawCOPPER::GetRunNo(int n)
357 	  {
358 	    CheckVersionSetBuffer();
359 	    return m_access->GetRunNo(n);
360 	  }
361
362
363 	  inline int RawCOPPER::GetSubRunNo(int n)
364 	  {
365 	    CheckVersionSetBuffer();
366 	    return m_access->GetSubRunNo(n);
367 	  }
368
369 	  inline unsigned int RawCOPPER::GetEveNo(int n)
370 	  {
371 	    CheckVersionSetBuffer();
372 	    return m_access->GetEveNo(n);
373 	  }
374
375
376 	  inline unsigned int RawCOPPER::GetNodeID(int n)
377 	  {
378 	    CheckVersionSetBuffer();
379 	    return m_access->GetNodeID(n);
380 	  }
381
382
383 	  inline int RawCOPPER::GetDataType(int n)
384 	  {
385 	    CheckVersionSetBuffer();
386 	    return m_access->GetDataType(n);
387 	  }
388
389 	  inline int RawCOPPER::GetTruncMask(int n)
390 	  {
391 	    CheckVersionSetBuffer();
392 	    return m_access->GetTruncMask(n);
393 	  }
394
395 	  inline unsigned int RawCOPPER::GetErrorBitFlag(int n)
396 	  {
397 	    CheckVersionSetBuffer();
398 	    return m_access->GetErrorBitFlag(n);
399 	  }
400
401 	  inline void RawCOPPER::AddErrorBitFlag(int n, unsigned int error_bit_flag)
402 	  {
403 	    CheckVersionSetBuffer();
404 	    return m_access->AddErrorBitFlag(n, error_bit_flag);
405 	  }
406
407
408 	  inline unsigned int RawCOPPER::GetCOPPERCounter(int n)
409 	  {
410 	    CheckVersionSetBuffer();
411 	    return m_access->GetCOPPERCounter(n);
412 	  }
413
414 	  inline int RawCOPPER::Get1stDetectorNwords(int n)
415 	  {
416 	    CheckVersionSetBuffer();
417 	    return m_access->Get1stDetectorNwords(n);
418 	  }
419
420 	  inline int RawCOPPER::Get2ndDetectorNwords(int n)
421 	  {
422 	    CheckVersionSetBuffer();
423 	    return m_access->Get2ndDetectorNwords(n);
424 	  }
425
426 	  inline int RawCOPPER::Get3rdDetectorNwords(int n)
427 	  {
428 	    CheckVersionSetBuffer();
429 	    return m_access->Get3rdDetectorNwords(n);
430 	  }
431
432 	  inline int RawCOPPER::Get4thDetectorNwords(int n)
433 	  {
434 	    CheckVersionSetBuffer();
435 	    return m_access->Get4thDetectorNwords(n);
436 	  }
437
438 	  inline int RawCOPPER::Get1stFINESSENwords(int n)
439 	  {
440 	    CheckVersionSetBuffer();
441 	    return m_access->Get1stFINESSENwords(n);
442 	  }
443
444 	  inline int RawCOPPER::Get2ndFINESSENwords(int n)
445 	  {
446 	    CheckVersionSetBuffer();
447 	    return m_access->Get2ndFINESSENwords(n);
448 	  }
449
450 	  inline int RawCOPPER::Get3rdFINESSENwords(int n)
451 	  {
452 	    CheckVersionSetBuffer();
453 	    return m_access->Get3rdFINESSENwords(n);
454 	  }
455
456 	  inline int RawCOPPER::Get4thFINESSENwords(int n)
457 	  {
458 	    CheckVersionSetBuffer();
459 	    return m_access->Get4thFINESSENwords(n);
460 	  }
461
462 	  inline int RawCOPPER::GetOffset1stFINESSE(int n)
463 	  {
464 	    CheckVersionSetBuffer();
465 	    return m_access->GetOffset1stFINESSE(n);
466 	  }
467
468 	  inline int RawCOPPER::GetOffset2ndFINESSE(int n)
469 	  {
470 	    CheckVersionSetBuffer();
471 	    return m_access->GetOffset2ndFINESSE(n);
472 	  }
473
474 	  inline int RawCOPPER::GetOffset3rdFINESSE(int n)
475 	  {
476 	    CheckVersionSetBuffer();
477 	    return m_access->GetOffset3rdFINESSE(n);
478 	  }
479
480 	  inline int RawCOPPER::GetOffset4thFINESSE(int n)
481 	  {
482 	    CheckVersionSetBuffer();
483 	    return m_access->GetOffset4thFINESSE(n);
484 	  }
485
486 	  inline int* RawCOPPER::Get1stFINESSEBuffer(int n)
487 	  {
488 	    CheckVersionSetBuffer();
489 	    return m_access->Get1stFINESSEBuffer(n);
490 	  }
491
492 	  inline int* RawCOPPER::Get2ndFINESSEBuffer(int n)
493 	  {
494 	    CheckVersionSetBuffer();
495 	    return m_access->Get2ndFINESSEBuffer(n);
496 	  }
497
498 	  inline int* RawCOPPER::Get3rdFINESSEBuffer(int n)
499 	  {
500 	    CheckVersionSetBuffer();
501 	    return m_access->Get3rdFINESSEBuffer(n);
502 	  }
503
504 	  inline int* RawCOPPER::Get4thFINESSEBuffer(int n)
505 	  {
506 	    CheckVersionSetBuffer();
507 	    return m_access->Get4thFINESSEBuffer(n);
508 	  }
509
510 	  inline int* RawCOPPER::Get1stDetectorBuffer(int n)
511 	  {
512 	    CheckVersionSetBuffer();
513 	    return m_access->Get1stDetectorBuffer(n);
514 	  }
515
516 	  inline int* RawCOPPER::Get2ndDetectorBuffer(int n)
517 	  {
518 	    CheckVersionSetBuffer();
519 	    return m_access->Get2ndDetectorBuffer(n);
520 	  }
521
522 	  inline int* RawCOPPER::Get3rdDetectorBuffer(int n)
523 	  {
524 	    CheckVersionSetBuffer();
525 	    return m_access->Get3rdDetectorBuffer(n);
526 	  }
527
528 	  inline int* RawCOPPER::Get4thDetectorBuffer(int n)
529 	  {
530 	    CheckVersionSetBuffer();
531 	    return m_access->Get4thDetectorBuffer(n);
532 	  }
533
534 	  inline int* RawCOPPER::GetExpRunSubrunBuf(int n)
535 	  {
536 	    CheckVersionSetBuffer();
537 	    return m_access->GetExpRunSubrunBuf(n);
538 	  }
539
540 	  inline unsigned int RawCOPPER::GetMagicDriverHeader(int n)
541 	  {
542 	    CheckVersionSetBuffer();
543 	    return m_access->GetMagicDriverHeader(n);
544 	  }
545
546 	  inline unsigned int RawCOPPER::GetMagicFPGAHeader(int n)
547 	  {
548 	    CheckVersionSetBuffer();
549 	    return m_access->GetMagicFPGAHeader(n);
550 	  }
551
552 	  inline unsigned int RawCOPPER::GetMagicFPGATrailer(int n)
553 	  {
554 	    CheckVersionSetBuffer();
555 	    return m_access->GetMagicFPGATrailer(n);
556 	  }
557
558 	  inline unsigned int RawCOPPER::GetMagicDriverTrailer(int n)
559 	  {
560 	    CheckVersionSetBuffer();
561 	    return m_access->GetMagicDriverTrailer(n);
562 	  }
563
564 	  inline unsigned int RawCOPPER::GetTrailerChksum(int  n)
565 	  {
566 	    CheckVersionSetBuffer();
567 	    return m_access->GetTrailerChksum(n);
568 	  }
569
570 	  inline unsigned int RawCOPPER::GetTTCtimeTRGType(int n)
571 	  {
572 	    CheckVersionSetBuffer();
573 	    return m_access->GetTTCtimeTRGType(n);
574 	  }
575
576 	  inline unsigned int RawCOPPER::GetTTUtime(int n)
577 	  {
578 	    CheckVersionSetBuffer();
579 	    return m_access->GetTTUtime(n);
580 	  }
581
582 	  inline int RawCOPPER::GetTTCtime(int n)
583 	  {
584 	    CheckVersionSetBuffer();
585 	    return m_access->GetTTCtime(n);
586 	  }
587
588 	  inline int RawCOPPER::GetTRGType(int n)
589 	  {
590 	    CheckVersionSetBuffer();
591 	    return m_access->GetTRGType(n);
592 	  }
593
594 	  inline void RawCOPPER::GetTTTimeVal(int n, struct timeval* tv)
595 	  {
596 	    CheckVersionSetBuffer();
597 	    return m_access->GetTTTimeVal(n, tv);
598 	  }
599
600 	  inline int RawCOPPER::GetBufferPos(int n)
601 	  {
602 	    CheckVersionSetBuffer();
603 	    return m_access->GetBufferPos(n);
604 	  }
605
606 	  inline   unsigned int RawCOPPER::CalcDriverChkSum(int n)
607 	  {
608 	    CheckVersionSetBuffer();
609 	    return m_access->CalcDriverChkSum(n);
610 	  }
611
612
613 	  inline  int RawCOPPER::GetNumFINESSEBlock(int n)
614 	  {
615 	    CheckVersionSetBuffer();
616 	    return m_access->GetNumFINESSEBlock(n);
617 	  }
618
619 	  inline  int RawCOPPER::GetDetectorNwords(int n, int finesse_num)
620 	  {
621 	    CheckVersionSetBuffer();
622 	    return m_access->GetDetectorNwords(n, finesse_num);
623 	  }
624
625 	  inline  int RawCOPPER::GetFINESSENwords(int n, int finesse_num)
626 	  {
627 	    CheckVersionSetBuffer();
628 	    return m_access->GetFINESSENwords(n, finesse_num);
629 	  }
630
631 	  inline  int RawCOPPER::GetOffsetFINESSE(int n, int finesse_num)
632 	  {
633 	    CheckVersionSetBuffer();
634 	    return m_access->GetOffsetFINESSE(n, finesse_num);
635 	  }
636
637 	  inline  int* RawCOPPER::GetFINESSEBuffer(int n, int finesse_num)
638 	  {
639 	    CheckVersionSetBuffer();
640 	    return m_access->GetFINESSEBuffer(n, finesse_num);
641 	  }
642
643 	  inline  int* RawCOPPER::GetDetectorBuffer(int n, int finesse_num)
644 	  {
645 	    CheckVersionSetBuffer();
646 	    return m_access->GetDetectorBuffer(n, finesse_num);
647 	  }
648
649 	  inline  unsigned int RawCOPPER::GetB2LFEE32bitEventNumber(int n)
650 	  {
651 	    CheckVersionSetBuffer();
652 	    return m_access->GetB2LFEE32bitEventNumber(n);
653 	  }
654
655 	  inline  unsigned int RawCOPPER::CalcXORChecksum(int* buf, int nwords)
656 	  {
657 	    CheckVersionSetBuffer();
658 	    return m_access->CalcXORChecksum(buf, nwords);
659 	  }
660
661 	  inline  void RawCOPPER::CheckData(int n,
662 	                                    unsigned int prev_evenum, unsigned int* cur_evenum_rawcprhdr,
663 	                                    unsigned int prev_copper_ctr, unsigned int* cur_copper_ctr,
664 	                                    unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no)
665 	  {
666
667 	    CheckVersionSetBuffer();
668 	    m_access->CheckData(n,
669 	                        prev_evenum, cur_evenum_rawcprhdr,
670 	                        prev_copper_ctr, cur_copper_ctr,
671 	                        prev_exprunsubrun_no,  cur_exprunsubrun_no);
672 	    return;
673 	  }
674
675 	  inline  bool RawCOPPER::CheckCOPPERMagic(int n)
676 	  {
677 	    CheckVersionSetBuffer();
678 	    return m_access->CheckCOPPERMagic(n);
679 	  }
680
681 	  inline  void RawCOPPER::CheckUtimeCtimeTRGType(int n)
682 	  {
683 	    CheckVersionSetBuffer();
684 	    return m_access->CheckUtimeCtimeTRGType(n);
685 	  }
686
687 	  inline  double RawCOPPER::GetEventUnixTime(int n)
688 	  {
689 	    CheckVersionSetBuffer();
690 	    return m_access->GetEventUnixTime(n);
691 	  }
692
693 	  inline  unsigned int RawCOPPER::GetB2LHeaderWord(int n, int finesse_buffer_pos)
694 	  {
695 	    CheckVersionSetBuffer();
696 	    return m_access->GetB2LHeaderWord(n, finesse_buffer_pos);
697 	  }
698
699 	  inline  unsigned int RawCOPPER::FillTopBlockRawHeader(unsigned int m_node_id, unsigned int m_data_type,
700 	                                                        unsigned int m_trunc_mask, unsigned int prev_eve32,
701 	                                                        unsigned int prev_exprunsubrun_no, unsigned int* cur_exprunsubrun_no)
702 	  {
703 	    CheckVersionSetBuffer();
704 	    return m_access->FillTopBlockRawHeader(m_node_id, m_data_type,
705 	                                           m_trunc_mask, prev_eve32,
706 	                                           prev_exprunsubrun_no, cur_exprunsubrun_no);
707 	  }
708
709 	#ifdef USE_B2LFEE_FORMAT_BOTH_VER1_AND_2
710 	  inline  void RawCOPPER::CheckB2LFEEHeaderVersion(int n)
711 	  {
712 	    CheckVersionSetBuffer();
713 	    return m_access->CheckB2LFEEHeaderVersion(n);
714 	  }
715 	#endif
716
717 	  inline void RawCOPPER::CheckVersionSetBuffer()
718 	  {
719 	    if (((m_buffer[ POS_FORMAT_VERSION ] & FORMAT_MASK) >> 8)  != m_version
720 	        || m_access == NULL) {
721 	      SetVersion();
722 	    }
723 	    m_access->SetBuffer(m_buffer, m_nwords, 0, m_num_events, m_num_nodes);
724 	  }
725 	}
726
727 	#endif
