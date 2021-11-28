GCC	= gcc
OpenMP_FLAG	= -fopenmp

all:
	$(GCC) -o CSRseq $(OpenMP_FLAG) CSRSeq.c 
	$(GCC) -o CSROpenMP $(OpenMP_FLAG) CSROpenMP.c
	$(GCC) -o CSCseq $(OpenMP_FLAG) CSCSeq.c
	$(GCC) -o CSCOpenMP $(OpenMP_FLAG) CSCOpenMP.c
CSRSeq: 
	$(GCC) -o CSRseq $(OpenMP_FLAG) CSRSeq.c 
CSROpenMP:
	$(GCC) -o CSROpenMP $(OpenMP_FLAG) CSROpenMP.c
CSCSeq:
	$(GCC) -o CSCseq $(OpenMP_FLAG) CSCSeq.c 
CSCOpenMP:
	$(GCC) -o CSCOpenMP $(OpenMP_FLAG) CSCOpenMP.c
clean:
	rm -f CSRseq CSROpenMP CSCseq CSCOpenMP 
	rm -f CSROpenMPvec1.txt CSROpenMPvec2.txt CSROpenMPvec3.txt
	rm -f CSRSeqvec1.txt CSRSeqvec2.txt CSRSeqvec3.txt
	rm -f CSCSeqvec1.txt CSCSeqvec2.txt CSCSeqvec3.txt
	rm -f CSCOpenMPvec1.txt CSCOpenMPvec2.txt CSCOpenMPvec3.txt
	rm -f matrix1.txtcsc.txt matrix2.txtcsc.txt matrix3.txtcsc.txt
	rm -f CSCvec1.txt CSCvec2.txt CSCvec3.txt
	rm -f CSRseqvec1.txt CSRseqvec2.txt CSRseqvec3.txt
	rm -f CSROpenMPvec1.txt CSROpenMPvec2.txt CSROpenMPvec3.txt
	rm -f CSCOpenMPvec1.txt CSCOpenMPvec2.txt CSCOpenMPvec3.txt