#include <stdio.h>
#include <sys/types.h>

#define UINT8 unsigned char
#define INT8 char

#define UINT16 __uint16_t 
#define INT16 __int16_t
	
#define UINT32 __uint32_t 
#define INT32 __int32_t

#define UINT64 __uint64_t
#define INT64 __int64_t

#define UINT128 __uint128_t
#define INT128 __int128_t

#define FLOAT64 double

extern "C" UINT64 getrsp();
extern "C" UINT64 testarmret();
extern "C" UINT64 testarmnop();
extern "C" UINT64 testarmmovz1();
extern "C" UINT64 testarmmovz2();
extern "C" UINT64 testarmmovz3();
extern "C" UINT64 testarmmovz4();
extern "C" UINT64 testarmmovk1();
extern "C" UINT64 testarmmovr1(UINT64);
extern "C" UINT64 testarmmovr2();
extern "C" UINT64 testarmmovn1();
extern "C" UINT64 testarmmovn2();
extern "C" UINT64 testarmmovn3();
extern "C" UINT64 testarmmovn4();
extern "C" UINT64 testarmmovn5();
extern "C" UINT64 testarmaddimmediate1();
extern "C" UINT64 testarmaddimmediate2();
extern "C" UINT64 testarmaddimmediate3();
extern "C" UINT64 testarmaddimmediate4();
extern "C" UINT64 testarmaddimmediate5();
extern "C" UINT64 testarmaddimmediate6();
extern "C" UINT64 testarmb1();
extern "C" UINT64 testarmb2();
extern "C" UINT64 testarmbdotcond1();
extern "C" UINT64 testarmbdotcond2();
extern "C" UINT64 testarmaddimmediate7();
extern "C" UINT64 testarmbdotcond3();
extern "C" UINT64 testarmbdotcond4();
extern "C" UINT64 testarmbdotcond5();
extern "C" UINT64 testarmbdotcond6();
extern "C" UINT64 testarmbdotcond7();
extern "C" UINT64 testarmbdotcond8();
extern "C" UINT64 testarmbdotcond9();
extern "C" UINT64 testarmbdotcond10();
extern "C" UINT64 testarmbdotcond11();
extern "C" UINT64 testarmbdotcond12();
extern "C" UINT64 testarmeqifcomma();
extern "C" UINT64 testarmneifcomma();
extern "C" UINT64 testarmeqifelsecomma();
extern "C" UINT64 testarmbeginequntilcomma();
extern "C" UINT64 testarmbeginnewhilerepeatcomma();
extern "C" UINT64 testarmsubimmediate1();
extern "C" UINT64 testarmsubimmediate2();
extern "C" UINT64 testarmsubimmediate3();
extern "C" UINT64 testarmsubimmediate4();
extern "C" UINT64 testarmsubimmediate5();
extern "C" UINT64 testarmsubimmediate6();
extern "C" UINT64 testarmaddextended1();
extern "C" UINT64 testarmaddextended2();
extern "C" UINT64 testarmaddextended3();
extern "C" UINT64 testarmaddextended4();
extern "C" UINT64 testarmaddextended5();
extern "C" UINT64 testarmaddextended6();
extern "C" UINT64 testarmaddextended7();
extern "C" UINT64 testarmaddextended8();
extern "C" UINT64 testarmaddextended9();
extern "C" UINT64 testarmaddsextended1();
extern "C" UINT64 testarmsubextended1();
extern "C" UINT64 testarmsubsextended1();
extern "C" UINT64 testarmcmpextended1();
extern "C" UINT64 testarmcmpextended2();
extern "C" UINT64 testarmcmnextended1();
extern "C" UINT64 testarmcmnextended2();
// extern "C" UINT64 testarmabs1();
// extern "C" UINT64 testarmabs2();
extern "C" UINT64 testarmaddshiftedreg1();
extern "C" UINT64 testarmaddshiftedreg2();
extern "C" UINT64 testarmaddshiftedreg3();
extern "C" UINT64 testarmaddshiftedreg4();
extern "C" UINT64 testarmaddsshiftedreg1();
extern "C" UINT64 testarmandshiftedreg1();
extern "C" UINT64 testarmbicshiftedreg1();
extern "C" UINT64 testarmorrshiftedreg1();
extern "C" UINT64 testarmornshiftedreg1();
extern "C" UINT64 testarmeorshiftedreg1();
extern "C" UINT64 testarmeonshiftedreg1();
extern "C" UINT64 testarmsubshiftedreg1();
extern "C" UINT64 testarmsubsshiftedreg1();
extern "C" UINT64 testarmsubsimmediate1();
extern "C" UINT64 testarmcmpimmediate1();
extern "C" UINT64 testarmcmpimmediate2();
extern "C" UINT64 testarmcmpimmediate3();
extern "C" UINT64 testarmcmnimmediate1();
extern "C" UINT64 testarmcmnimmediate2();
extern "C" UINT64 testarmcmnimmediate3();
extern "C" UINT64 testarmcmnshiftedreg1();
extern "C" UINT64 testarmcmnshiftedreg2();
extern "C" UINT64 testarmandsshiftedreg1();
extern "C" UINT64 testarmandsshiftedreg2();
extern "C" UINT64 testarmbicsshiftedreg1();
extern "C" UINT64 testarmbicsshiftedreg2();
extern "C" UINT64 testarmcmpshiftedreg1();
extern "C" UINT64 testarmcmpshiftedreg2();
extern "C" UINT64 testarmtstshiftedreg1();
extern "C" UINT64 testarmtstshiftedreg2();
extern "C" UINT64 testarmldrlit1();
extern "C" UINT64 testarmldrlit2();
extern "C" UINT64 testarmldrlit3();
extern "C" UINT64 testarmadrarmldrimm1();
extern "C" UINT64 testarmadrarmldrimm2();
extern "C" UINT64 testarmadrarmldrimm3();
extern "C" UINT64 testarmldrimmplusplus1();
extern "C" UINT64 getptestconstant1();
extern "C" UINT64 testarmldrimmplusplus2();
extern "C" UINT64 testarmimmplusplusldr1();
extern "C" UINT64 testarmimmplusplusldr2();
extern "C" UINT64 testarmimmplusplusldr3();
extern "C" UINT64 testarmldrreg1();
extern "C" UINT64 testarmldrreg2();
extern "C" UINT64 testarmldrreg3();
extern "C" UINT64 testarmldrreg4();
extern "C" UINT64 testarmldrreg5();
extern "C" UINT64 testarmldrreg6();
extern "C" UINT64 testarmmovsp1();
extern "C" UINT64 testarmpushsp1();
extern "C" UINT64 testarmpushsp2();
extern "C" UINT64 testarmpopsp1();
extern "C" UINT64 testarmpopsp2();
extern "C" UINT64 testarmstrimm1();
extern "C" UINT64 testarmstrimm2();
extern "C" UINT64 testarmstrimm3();
extern "C" UINT64 testarmstrimm4();
extern "C" UINT64 testarmstrimm5();
extern "C" UINT64 testarmstrimm6();
extern "C" UINT64 testarmsbfm1();
extern "C" UINT64 testarmsbfm2();
extern "C" UINT64 testarmsbfm3();
extern "C" UINT64 testarmsbfm4();
extern "C" UINT64 testarmsbfm5();
extern "C" UINT64 testarmsbfm6();
extern "C" UINT64 testarmubfm1();
extern "C" UINT64 testarmubfm2();
extern "C" UINT64 testarmubfm3();
extern "C" UINT64 testarmubfm4();
extern "C" UINT64 testarmubfm5();
extern "C" UINT64 testarmubfm6();
extern "C" UINT64 testarmmadd1();
extern "C" UINT64 testarmudiv1();
extern "C" UINT64 testarmsdiv1();
extern "C" UINT64 testarmumulh1();
extern "C" UINT64 testarmasrimmediate1();
extern "C" UINT64 testarmasrimmediate2();
extern "C" UINT64 testarmasrimmediate3();
extern "C" UINT64 testarmasrimmediate4();
extern "C" UINT64 testarmasrimmediate5();
extern "C" UINT64 testarmasrimmediate6();
extern "C" UINT64 testarmasrimmediate7();
extern "C" UINT64 testarmlsrimmediate1();
extern "C" UINT64 testarmlsrimmediate2();
extern "C" UINT64 testarmlsrimmediate3();
extern "C" UINT64 testarmlsrimmediate4();
extern "C" UINT64 testarmlsrimmediate5();
extern "C" UINT64 testarmlsrimmediate6();
extern "C" UINT64 testarmlsrimmediate7();
extern "C" UINT64 testarmlslimmediate1();
extern "C" UINT64 testarmlslimmediate2();
extern "C" UINT64 testarmlslimmediate3();
extern "C" UINT64 testarmlslimmediate4();
extern "C" UINT64 testarmasrreg1();
extern "C" UINT64 testarmasrreg2();
extern "C" UINT64 testarmasrreg3();
extern "C" UINT64 testarmasrreg4();
extern "C" UINT64 testarmasrreg5();
extern "C" UINT64 testarmasrreg6();
extern "C" UINT64 testarmasrreg7();
extern "C" UINT64 testarmlsrreg1();
extern "C" UINT64 testarmlsrreg2();
extern "C" UINT64 testarmlsrreg3();
extern "C" UINT64 testarmlsrreg4();
extern "C" UINT64 testarmlsrreg5();
extern "C" UINT64 testarmlsrreg6();
extern "C" UINT64 testarmlsrreg7();
extern "C" UINT64 testarmlslreg1();
extern "C" UINT64 testarmlslreg2();
extern "C" UINT64 testarmlslreg3();
extern "C" UINT64 testarmlslreg4();
extern "C" UINT64 testquerymovzork1();
extern "C" UINT64 testquerymovzork2();
extern "C" UINT64 testquerymovnork1();
extern "C" UINT64 testquerymovnork2();
extern "C" UINT64 testntoir64a();
extern "C" UINT64 testntoir64b();
extern "C" UINT64 testntoir64c();
extern "C" UINT64 testntoir64d();
extern "C" UINT64 testntoir64e();
extern "C" UINT64 testntoir64f();
extern "C" UINT64 testntoir64g();
extern "C" UINT64 testntoir64h();
extern "C" UINT64 testntoir64i();
extern "C" UINT64 testntoir64j();
extern "C" UINT64 testntoir64k();
extern "C" UINT64 testntoir64l();
extern "C" UINT64 testntoir64m();
extern "C" UINT64 testntoir64n();
extern "C" UINT64 testntoir64o();
extern "C" UINT64 testntoir64p();
extern "C" UINT64 testntoir64q();
extern "C" UINT64 testntoir64r();
extern "C" UINT64 testntoir64s();
extern "C" UINT64 testntoir64t();
extern "C" UINT64 testntoir64u();
extern "C" UINT64 testntoir64v();
extern "C" UINT64 testntoir64w();
extern "C" UINT64 testntoir64x();
extern "C" UINT64 testntoir64y();
extern "C" UINT64 testntoir64z();
extern "C" UINT64 testntoir64aa();
extern "C" UINT64 testntoir64ab();
extern "C" UINT64 testntoir64ac();
extern "C" UINT64 testir64toir64();
extern "C" UINT64 testpcplusntoir64a();
extern "C" UINT64 testpcplusntoir64b();
extern "C" UINT64 testpcplusntoir64c();
extern "C" UINT64 testpcplusntoir64d();
extern "C" UINT64 testpcplusntoir64e();
extern "C" UINT64 testpcplusntoir64f();
extern "C" UINT64 testpcplusntoir64g();
extern "C" UINT64 testpcplusntoir64h();
extern "C" UINT64 testpctoir64a();
extern "C" UINT64 testpcplusntopca();
extern "C" UINT64 testpcplusntopcb();
extern "C" UINT64 testpcplusntopcc();
extern "C" UINT64 testir64plusntoir64a();
extern "C" UINT64 testir64plusntoir64b();
extern "C" UINT64 testir64plusntoir64c();
extern "C" UINT64 testir64plusntoir64d();
extern "C" UINT64 testir64plusntoir64e();
extern "C" UINT64 testir64plusntoir64f();
extern "C" UINT64 testir64plusntoir64g();
extern "C" UINT64 testir64plusntoir64h();
extern "C" UINT64 testir64plusntoir64i();
extern "C" UINT64 testrspplusntorspa();
extern "C" UINT64 testbracketir64toir64a();
extern "C" UINT64 testbracketir64toir64b();
extern "C" UINT64 testrsptoir64a();
extern "C" UINT64 testir64torspa();
extern "C" UINT64 testrspplusntoir64a();
extern "C" UINT64 testrspplusntoir64b();
extern "C" UINT64 testrspplusntoir64c();
extern "C" UINT64 testrspplusntoir64d();
extern "C" UINT64 testbracketpcplusntoir64a();
extern "C" UINT64 testbracketpcplusntoir64b();
extern "C" UINT64 testbracketpcplusntoir64c();
extern "C" UINT64 testotoir64a();
extern "C" UINT64 testbracketotoir64a();
extern "C" UINT64 testir64tobracketir64a();
extern "C" UINT64 testbracketir64plusir64toir64a();
extern "C" UINT64 testir64tobracketir64plusir64a();
extern "C" UINT64 testbracketir64plusntoir64a();
extern "C" UINT64 testbracketir64plusntoir64b();
extern "C" UINT64 testbracketir64plusntoir64c();
extern "C" UINT64 testbracketir64plusntoir64d();
extern "C" UINT64 testbracketir64plusntoir64e();
extern "C" UINT64 testbracketir64plusntoir64f();
extern "C" UINT64 testbracketir64plusntoir64g();
extern "C" UINT64 testbracketir64plusntoir64h();
extern "C" UINT64 testarmcfinva();
extern "C" UINT64 testarmcfinvb();
extern "C" UINT64 testbracketir64toir64plusna();
extern "C" UINT64 testbracketir64toir64plusnb();
extern "C" UINT64 testbracketrspplusntoir64a();
extern "C" UINT64 testbracketrspplusntoir64b();
extern "C" UINT64 testir64tobracketrspplusna();
extern "C" UINT64 testir64tobracketrspplusnb();
extern "C" UINT64 testir64ir64toir64opa();
extern "C" UINT64 testir64ir64toir64opb();
extern "C" UINT64 testir64ir64toir64idpfa();
extern "C" UINT64 testir64ir64toir64idpfb();
extern "C" UINT64 testir64ir64toir64idpfc();
extern "C" UINT64 testir64ir64toir64idpfd();
extern "C" UINT64 testir64ir64toir64idpfe();
extern "C" UINT64 testir64ir64toir64idpff();
extern "C" UINT64 testir64ir64toir64idpfg();
extern "C" UINT64 testir64ir64toir64idpfh();
extern "C" UINT64 testir64ir64toir64idpfi();
extern "C" UINT64 testir64ir64toir64idpfj();
extern "C" UINT64 testir64ir64toir64idpfk();
extern "C" UINT64 testir64ir64toir64idpfl();
extern "C" UINT64 testir64ir64toir64idpfm();
extern "C" UINT64 testir64ir64toir64idpfn();
extern "C" UINT64 testir64ir64toir64idpfo();
extern "C" UINT64 testir64ir64toir64idpfp();
extern "C" UINT64 testir64ir64toir64idpfq();
extern "C" UINT64 testir64ir64toir64idpfr();
extern "C" UINT64 testir64ir64toir64idpfs();
extern "C" UINT64 testir64ir64toir64idpft();
extern "C" UINT64 testir64ir64toir64idpfu();
extern "C" UINT64 testir64ir64toir64idpfv();
extern "C" UINT64 testir64ir64toir64idpfw();
extern "C" UINT64 testir64ir64toir64idpfx();
extern "C" UINT64 testir64ir64toir64idpfy();
extern "C" UINT64 testir64ir64toir64idcfa();
extern "C" UINT64 testir64ir64toir64idcfb();
extern "C" UINT64 testir64ir64toir64idcfc();
extern "C" UINT64 testir64ir64toir64idcfd();
extern "C" UINT64 testir64ir64toir64idcfe();
extern "C" UINT64 testir64ir64toir64idcff();
extern "C" UINT64 testir64ir64toir64idcfg();
extern "C" UINT64 testir64ir64toir64idcfh();
extern "C" UINT64 testir64ir64toir64idcfi();
extern "C" UINT64 testir64ir64toir64idcfj();
extern "C" UINT64 testir64ir64toir64idcfk();
extern "C" UINT64 testir64ir64toir64idcfl();
extern "C" UINT64 testir64ir64toir64idcfm();
extern "C" UINT64 testir64ir64toir64idcfn();
extern "C" UINT64 testir64ir64toir64idcfo();
extern "C" UINT64 testir64ir64toir64idcfp();
extern "C" UINT64 testir64ir64toir64idcfq();
extern "C" UINT64 testir64ir64toir64idcfr();
extern "C" UINT64 testir64ir64toir64idcfs();
extern "C" UINT64 testir64ir64toir64idcft();
extern "C" UINT64 testir64ir64toir64idcfu();
extern "C" UINT64 testir64ir64toir64idcfv();
extern "C" UINT64 testir64ir64toir64idcfw();
extern "C" UINT64 testir64ir64toir64idcfx();
extern "C" UINT64 testir64ir64toir64idcfy();
extern "C" UINT64 testir64ir64toir64idcfz();
extern "C" UINT64 testir64ir64toir64idcfaa();
extern "C" UINT64 testir64ir64toir64idcfab();
extern "C" UINT64 testir64ir64toir64idcfac();
extern "C" UINT64 testir64ir64toir64idcfad();
extern "C" UINT64 testir64ir64toir64idcfae();
extern "C" UINT64 testir64ir64toir64idcfaf();
extern "C" UINT64 testir64ir64toir64idcfag();
extern "C" UINT64 testir64ir64toir64idcfah();
extern "C" UINT64 testir64ir64toir64idcfai();
extern "C" UINT64 testir64ir64toir64idcfaj();
extern "C" UINT64 testir64ir64toir64idcfak();
extern "C" UINT64 testir64ir64toir64idcfal();
extern "C" UINT64 testir64ir64toir64idcfam();
extern "C" UINT64 testir64ir64toir64idcfan();
extern "C" UINT64 testir64ir64toir64idcfao();
extern "C" UINT64 testir64ir64toir64idcfap();
extern "C" UINT64 testir64ir64toir64idcfaq();
extern "C" UINT64 testir64ir64toir64idcfar();
extern "C" UINT64 testir64ir64toir64idcfas();
extern "C" UINT64 testir64ir64toir64idcfat();
extern "C" UINT64 testir64ir64toir64idcfau();
extern "C" UINT64 testir64ir64toir64idcfav();
extern "C" UINT64 testir64ir64toir64idcfaw();
extern "C" UINT64 testir64ir64toir64idcfax();
extern "C" UINT64 testir64ir64toir64idcfay();
extern "C" UINT64 testir64ir64toir64idcfaz();
extern "C" UINT64 testir64ir64toir64idcfba();
extern "C" UINT64 testir64ir64toir64idcfbb();
extern "C" UINT64 testir64ir64toir64idcfbc();
extern "C" UINT64 testir64ir64toir64idcfbd();
extern "C" UINT64 testir64ir64toir64idcfbe();
extern "C" UINT64 testir64ir64toir64idcfbf();
extern "C" UINT64 testir64ir64toir64idcfbg();
extern "C" UINT64 testir64ir64toir64idcfbh();
extern "C" UINT64 testir64ir64toir64idcfbi();
extern "C" UINT64 testir64ir64toir64idcfbj();
extern "C" UINT64 testir64ir64toir64idcfbk();
extern "C" UINT64 testir64ir64toir64idcfbl();
extern "C" UINT64 testir64ir64toir64idcfbm();
extern "C" UINT64 testir64ir64toir64idcfbn();
extern "C" UINT64 testir64ir64toir64idcfbo();
extern "C" UINT64 testir64ir64toir64idcfbp();
extern "C" UINT64 testir64ntoir64idpfa();
extern "C" UINT64 testir64ntoir64idpfb();
extern "C" UINT64 testir64ntoir64idpfc();
extern "C" UINT64 testir64ntoir64idpfd();
extern "C" UINT64 testir64ntoir64idpfe();
extern "C" UINT64 testir64ntoir64idpff();
extern "C" UINT64 testir64ntoir64idpfg();
extern "C" UINT64 testarmandimmediatea();
extern "C" UINT64 testarmandimmediateb();
extern "C" UINT64 testarmandimmediatec();
extern "C" UINT64 testarmandimmediated();
extern "C" UINT64 testarmandimmediatee();
extern "C" UINT64 testarmandimmediatef();
extern "C" UINT64 testarmandimmediateg();
extern "C" UINT64 testarmandimmediateh();
extern "C" UINT64 testarmandimmediatei();
extern "C" UINT64 testarmandimmediatej();
extern "C" UINT64 testarmandimmediatek();
extern "C" UINT64 testarmorimmediatea();
extern "C" UINT64 testarmorimmediateb();
extern "C" UINT64 testarmandimmediatel();
extern "C" UINT64 testarmorimmediatec();
extern "C" UINT64 testarmeorimmediatea();
extern "C" UINT64 testir64ntoir64idpfh();
extern "C" UINT64 testir64ntoir64idpfi();

extern "C" UINT64 testir64ntoir64idcfa();
extern "C" UINT64 testir64ntoir64idcfa2();
extern "C" UINT64 testir64ntoir64idcfa3();
extern "C" UINT64 testir64ntoir64idcfb();
extern "C" UINT64 testir64ntoir64idcfb2();
extern "C" UINT64 testir64ntoir64idcfb3();
extern "C" UINT64 testir64ntoir64idcfc();
extern "C" UINT64 testir64ntoir64idcfc2();
extern "C" UINT64 testir64ntoir64idcfc3();
extern "C" UINT64 testir64ntoir64idcfd();
extern "C" UINT64 testir64ntoir64idcfd2();
extern "C" UINT64 testir64ntoir64idcfd3();
extern "C" UINT64 testir64ntoir64idcfe();
extern "C" UINT64 testir64ntoir64idcfe2();
extern "C" UINT64 testir64ntoir64idcfe3();
extern "C" UINT64 testir64ntoir64idcff();
extern "C" UINT64 testir64ntoir64idcff2();
extern "C" UINT64 testir64ntoir64idcff3();
extern "C" UINT64 testir64ntoir64idcfg();
extern "C" UINT64 testir64ntoir64idcfg2();
extern "C" UINT64 testir64ntoir64idcfg3();
extern "C" UINT64 testmatoscratchreg2a();
extern "C" UINT64 testmatoscratchreg2b();
extern "C" UINT64 testmatoscratchreg2c();
extern "C" UINT64 testmatoscratchreg2d();
extern "C" UINT64 testmatoscratchreg2e();
extern "C" UINT64 testmatoscratchreg2f();
extern "C" UINT64 testmatoscratchreg2g();
extern "C" UINT64 testmbtoscratchreg1a();
extern "C" UINT64 testmbtoscratchreg1b();
extern "C" UINT64 testmbtoscratchreg1c();
extern "C" UINT64 testmbtoscratchreg1d();
extern "C" UINT64 testmbtoscratchreg1e();
extern "C" UINT64 testmbtoscratchreg1f();
extern "C" UINT64 testmbtoscratchreg1g();
extern "C" UINT64 testscratchreg2tomdesta();
extern "C" UINT64 testscratchreg2tomdestb();
extern "C" UINT64 testscratchreg2tomdestc();

extern "C" UINT64 testnir64toir64idpfa();
extern "C" UINT64 testnir64toir64idpfb();
extern "C" UINT64 testnir64toir64idpfc();
extern "C" UINT64 testnir64toir64idpfd();
extern "C" UINT64 testnir64toir64idpfe();
extern "C" UINT64 testnir64toir64idpff();

extern "C" UINT64 testir64ir64toir64ida();
extern "C" UINT64 testir64ir64toir64idb();
extern "C" UINT64 testir64ir64toir64idc();

extern "C" UINT64 testir64ntoir64ida();
extern "C" UINT64 testir64ntoir64idb();
extern "C" UINT64 testir64ntoir64idc();

extern "C" UINT64 testnir64toir64ida();
extern "C" UINT64 testnir64toir64idb();
extern "C" UINT64 testnir64toir64idc();

extern "C" UINT64 testaddcommaa();
extern "C" UINT64 testaddcommab();
extern "C" UINT64 testaddcommac();
extern "C" UINT64 testaddcommad();
extern "C" UINT64 testaddcommae();
extern "C" UINT64 testaddcommaf();
extern "C" UINT64 testaddcommag();

extern "C" UINT64 testadccommaa();
extern "C" UINT64 testsbccommaa();
extern "C" UINT64 testsdivcommaa();
extern "C" UINT64 testasrcommaa();
extern "C" UINT64 testlsrcommaa();
extern "C" UINT64 testmulcommaa();
extern "C" UINT64 testudivcommaa();
extern "C" UINT64 testlslcommaa();
extern "C" UINT64 testrorcommaa();
extern "C" UINT64 testandcommaa();
extern "C" UINT64 testorcommaa();
extern "C" UINT64 testxorcommaa();
extern "C" UINT64 testnandcommaa();
extern "C" UINT64 testnorcommaa();
extern "C" UINT64 testxnorcommaa();
extern "C" UINT64 testbiccommaa();
extern "C" UINT64 testorncommaa();
extern "C" UINT64 testumulhcommaa();
extern "C" UINT64 testsmulhcommaa();
extern "C" UINT64 testandcommab();
extern "C" UINT64 testaddcommah();
extern "C" UINT64 testaddcommai();
extern "C" UINT64 testaddcommaj();
extern "C" UINT64 testaddcommak();
extern "C" UINT64 testaddcommal();
extern "C" UINT64 testaddcommam();
extern "C" UINT64 testaddcomman();
extern "C" UINT64 testaddcommao();
extern "C" UINT64 testaddcommap();
extern "C" UINT64 testaddcommaq();
extern "C" UINT64 testaddcommar();
extern "C" UINT64 testaddcommas();
extern "C" UINT64 testaddcommat();
extern "C" UINT64 testaddcommau();
extern "C" UINT64 testsubcommaa();
extern "C" UINT64 testsubcommab();
extern "C" UINT64 testsubcommac();

extern "C" UINT64 testir64plusplusntoir64a();
extern "C" UINT64 testir64plusplusntoir64b();
extern "C" UINT64 testir64plusplusntoir64c();
extern "C" UINT64 testir64plusplusntoir64d();
extern "C" UINT64 testir64thenplusplusntoir64a();
extern "C" UINT64 testir64thenplusplusntoir64b();
extern "C" UINT64 testir64thenplusplusntoir64c();
extern "C" UINT64 testir64thenplusplusntoir64d();
extern "C" UINT64 testir64toir64plusplusna();
extern "C" UINT64 testir64toir64plusplusnb();
extern "C" UINT64 testir64toir64plusplusnc();
extern "C" UINT64 testir64toir64plusplusnd();
extern "C" UINT64 testir64toir64thenplusplusna();
extern "C" UINT64 testir64toir64thenplusplusnb();
extern "C" UINT64 testir64toir64thenplusplusnc();
extern "C" UINT64 testir64toir64thenplusplusnd();

extern "C" UINT64 testaddcommav();
extern "C" UINT64 testaddcommaw();
extern "C" UINT64 testaddcommax();
extern "C" UINT64 testaddcommay();
extern "C" UINT64 testaddcommaz();
extern "C" UINT64 testaddcommaaa();
extern "C" UINT64 testaddcommaab();
extern "C" UINT64 testaddcommaac();
extern "C" UINT64 testaddcommaad();
extern "C" UINT64 testaddcommaae();
extern "C" UINT64 testaddcommaaf();
extern "C" UINT64 testaddcommaag();

extern "C" UINT64 testarmldrbimma();
extern "C" UINT64 testarmldrhimma();
extern "C" UINT64 testarmldrwimma();
extern "C" UINT64 testarmldrximma();
extern "C" UINT64 testarmldrsbwimma();
extern "C" UINT64 testarmldrsbximma();
extern "C" UINT64 testarmldrshwimma();
extern "C" UINT64 testarmldrshximma();
extern "C" UINT64 testarmldrswximma();

extern "C" UINT64 testarmldrbimmplusplusa();
extern "C" UINT64 testarmldrbimmplusplusb();
extern "C" UINT64 testarmldrhimmplusplusa();
extern "C" UINT64 testarmldrhimmplusplusb();
extern "C" UINT64 testarmldrwimmplusplusa();
extern "C" UINT64 testarmldrwimmplusplusb();
extern "C" UINT64 testarmldrximmplusplusa();
extern "C" UINT64 testarmldrximmplusplusb();

extern "C" UINT64 testarmimmplusplusldrba();
extern "C" UINT64 testarmimmplusplusldrbb();
extern "C" UINT64 testarmimmplusplusldrha();
extern "C" UINT64 testarmimmplusplusldrhb();
extern "C" UINT64 testarmimmplusplusldrwa();
extern "C" UINT64 testarmimmplusplusldrwb();
extern "C" UINT64 testarmimmplusplusldrxa();
extern "C" UINT64 testarmimmplusplusldrxb();

extern "C" UINT64 testarmstrbimma();
extern "C" UINT64 testarmstrhimma();
extern "C" UINT64 testarmstrwimma();
extern "C" UINT64 testarmstrximma();

extern "C" UINT64 testarmimmplusplusldrsbwa();
extern "C" UINT64 testarmimmplusplusldrsbwb();
extern "C" UINT64 testarmimmplusplusldrsbxa();
extern "C" UINT64 testarmimmplusplusldrsbxb();
extern "C" UINT64 testarmimmplusplusldrshwa();
extern "C" UINT64 testarmimmplusplusldrshwb();
extern "C" UINT64 testarmimmplusplusldrshxa();
extern "C" UINT64 testarmimmplusplusldrshxb();
extern "C" UINT64 testarmimmplusplusldrswxa();
extern "C" UINT64 testarmimmplusplusldrswxb();

extern "C" UINT64 testarmimmplusplusstrba();
extern "C" UINT64 testarmimmplusplusstrbb();
extern "C" UINT64 testarmimmplusplusstrha();
extern "C" UINT64 testarmimmplusplusstrhb();
extern "C" UINT64 testarmimmplusplusstrwa();
extern "C" UINT64 testarmimmplusplusstrwb();
extern "C" UINT64 testarmimmplusplusstrxa();
extern "C" UINT64 testarmimmplusplusstrxb();

extern "C" UINT64 testarmstrbimmplusplusa();
extern "C" UINT64 testarmstrbimmplusplusb();
extern "C" UINT64 testarmstrhimmplusplusa();
extern "C" UINT64 testarmstrhimmplusplusb();
extern "C" UINT64 testarmstrwimmplusplusa();
extern "C" UINT64 testarmstrwimmplusplusb();
extern "C" UINT64 testarmstrximmplusplusa();
extern "C" UINT64 testarmstrximmplusplusb();

extern "C" UINT64 testarmldrbrega();
extern "C" UINT64 testarmldrhrega();
extern "C" UINT64 testarmldrwrega();
extern "C" UINT64 testarmldrxrega();

extern "C" UINT64 testarmldrsbwrega();
extern "C" UINT64 testarmldrsbxrega();
extern "C" UINT64 testarmldrshwrega();
extern "C" UINT64 testarmldrshxrega();
extern "C" UINT64 testarmldrswxrega();

extern "C" UINT64 testarmstrbrega();
extern "C" UINT64 testarmstrhrega();
extern "C" UINT64 testarmstrwrega();
extern "C" UINT64 testarmstrxrega();

extern "C" UINT64 testarmldrswlita();

extern "C" UINT64 testarmcbnza();
extern "C" UINT64 testarmcbnzb();

extern "C" UINT64 testarmcbza();
extern "C" UINT64 testarmcbzb();

extern "C" UINT64 testbracketir64plusir64toirsza();
extern "C" UINT64 testbracketir64plusir64toirszb();

extern "C" UINT64 testirsztobracketir64plusir64a();

extern "C" UINT64 testbracketir64toirsza();
extern "C" UINT64 testbracketir64toirszb();

extern "C" UINT64 testirsztobracketir64a();

extern "C" UINT64 testbracketir64plusntoirsza();
extern "C" UINT64 testbracketir64plusntoirszb();
extern "C" UINT64 testbracketir64plusntoirszc();
extern "C" UINT64 testbracketir64plusntoirszd();
extern "C" UINT64 testbracketir64plusntoirsze();
extern "C" UINT64 testbracketir64plusntoirszf();
extern "C" UINT64 testbracketir64plusntoirszg();

extern "C" UINT64 testbracketir64plusntoirszh();
extern "C" UINT64 testbracketir64plusntoirszi();
extern "C" UINT64 testbracketir64plusntoirszj();
extern "C" UINT64 testbracketir64plusntoirszk();
extern "C" UINT64 testbracketir64plusntoirszl();
extern "C" UINT64 testbracketir64plusntoirszm();
extern "C" UINT64 testbracketir64plusntoirszn();

extern "C" UINT64 testirsztobracketir64plusna();
extern "C" UINT64 testirsztobracketir64plusnb();
extern "C" UINT64 testirsztobracketir64plusnc();
extern "C" UINT64 testirsztobracketir64plusnd();
extern "C" UINT64 testirsztobracketir64plusne();
extern "C" UINT64 testirsztobracketir64plusnf();
extern "C" UINT64 testirsztobracketir64plusng();

extern "C" UINT64 testbracketpcplusntoirsza();
extern "C" UINT64 testbracketpcplusntoirszb();
extern "C" UINT64 testbracketpcplusntoirszc();
extern "C" UINT64 testbracketpcplusntoirszd();
extern "C" UINT64 testbracketpcplusntoirsze();
extern "C" UINT64 testbracketpcplusntoirszf();
extern "C" UINT64 testbracketpcplusntoirszg();

extern "C" UINT64 testbracketotoirsza();

extern "C" UINT64 testbracketir64plusplusntoirsza();
extern "C" UINT64 testbracketir64plusplusntoirsza2();
extern "C" UINT64 testbracketir64plusplusntoirszb();
extern "C" UINT64 testbracketir64plusplusntoirszb2();
extern "C" UINT64 testbracketir64plusplusntoirszc();
extern "C" UINT64 testbracketir64plusplusntoirszc2();
extern "C" UINT64 testbracketir64plusplusntoirszd();
extern "C" UINT64 testbracketir64plusplusntoirszd2();
extern "C" UINT64 testbracketir64plusplusntoirsze();
extern "C" UINT64 testbracketir64plusplusntoirsze2();
extern "C" UINT64 testbracketir64plusplusntoirszf();
extern "C" UINT64 testbracketir64plusplusntoirszf2();
extern "C" UINT64 testbracketir64plusplusntoirszg();
extern "C" UINT64 testbracketir64plusplusntoirszg2();
extern "C" UINT64 testbracketir64plusplusntoirszh();
extern "C" UINT64 testbracketir64plusplusntoirszh2();
extern "C" UINT64 testbracketir64plusplusntoirszi();
extern "C" UINT64 testbracketir64plusplusntoirszi2();
extern "C" UINT64 testbracketir64plusplusntoirszj();
extern "C" UINT64 testbracketir64plusplusntoirszj2();
extern "C" UINT64 testbracketir64plusplusntoirszk();
extern "C" UINT64 testbracketir64plusplusntoirszk2();
extern "C" UINT64 testbracketir64plusplusntoirszl();
extern "C" UINT64 testbracketir64plusplusntoirszl2();
extern "C" UINT64 testbracketir64plusplusntoirszm();
extern "C" UINT64 testbracketir64plusplusntoirszm2();
extern "C" UINT64 testbracketir64plusplusntoirszn();
extern "C" UINT64 testbracketir64plusplusntoirszn2();

extern "C" UINT64 testbracketir64thenplusplusntoirsza();
extern "C" UINT64 testbracketir64thenplusplusntoirsza2();
extern "C" UINT64 testbracketir64thenplusplusntoirszb();
extern "C" UINT64 testbracketir64thenplusplusntoirszb2();
extern "C" UINT64 testbracketir64thenplusplusntoirszc();
extern "C" UINT64 testbracketir64thenplusplusntoirszc2();
extern "C" UINT64 testbracketir64thenplusplusntoirszd();
extern "C" UINT64 testbracketir64thenplusplusntoirszd2();
extern "C" UINT64 testbracketir64thenplusplusntoirsze();
extern "C" UINT64 testbracketir64thenplusplusntoirsze2();
extern "C" UINT64 testbracketir64thenplusplusntoirszf();
extern "C" UINT64 testbracketir64thenplusplusntoirszf2();
extern "C" UINT64 testbracketir64thenplusplusntoirszg();
extern "C" UINT64 testbracketir64thenplusplusntoirszg2();
extern "C" UINT64 testbracketir64thenplusplusntoirszh();
extern "C" UINT64 testbracketir64thenplusplusntoirszh2();
extern "C" UINT64 testbracketir64thenplusplusntoirszi();
extern "C" UINT64 testbracketir64thenplusplusntoirszi2();
extern "C" UINT64 testbracketir64thenplusplusntoirszj();
extern "C" UINT64 testbracketir64thenplusplusntoirszj2();
extern "C" UINT64 testbracketir64thenplusplusntoirszk();
extern "C" UINT64 testbracketir64thenplusplusntoirszk2();
extern "C" UINT64 testbracketir64thenplusplusntoirszl();
extern "C" UINT64 testbracketir64thenplusplusntoirszl2();
extern "C" UINT64 testbracketir64thenplusplusntoirszm();
extern "C" UINT64 testbracketir64thenplusplusntoirszm2();
extern "C" UINT64 testbracketir64thenplusplusntoirszn();
extern "C" UINT64 testbracketir64thenplusplusntoirszn2();

extern "C" UINT64 testirsztobracketir64plusplusna();
extern "C" UINT64 testirsztobracketir64plusplusna2();
extern "C" UINT64 testirsztobracketir64plusplusnb();
extern "C" UINT64 testirsztobracketir64plusplusnb2();
extern "C" UINT64 testirsztobracketir64plusplusnc();
extern "C" UINT64 testirsztobracketir64plusplusnc2();
extern "C" UINT64 testirsztobracketir64plusplusnd();
extern "C" UINT64 testirsztobracketir64plusplusnd2();
extern "C" UINT64 testirsztobracketir64plusplusne();
extern "C" UINT64 testirsztobracketir64plusplusne2();
extern "C" UINT64 testirsztobracketir64plusplusnf();
extern "C" UINT64 testirsztobracketir64plusplusnf2();
extern "C" UINT64 testirsztobracketir64plusplusng();
extern "C" UINT64 testirsztobracketir64plusplusng2();
extern "C" UINT64 testirsztobracketir64plusplusnh();
extern "C" UINT64 testirsztobracketir64plusplusnh2();

extern "C" UINT64 testirsztobracketir64thenplusplusna();
extern "C" UINT64 testirsztobracketir64thenplusplusna2();
extern "C" UINT64 testirsztobracketir64thenplusplusnb();
extern "C" UINT64 testirsztobracketir64thenplusplusnb2();
extern "C" UINT64 testirsztobracketir64thenplusplusnc();
extern "C" UINT64 testirsztobracketir64thenplusplusnc2();
extern "C" UINT64 testirsztobracketir64thenplusplusnd();
extern "C" UINT64 testirsztobracketir64thenplusplusnd2();
extern "C" UINT64 testirsztobracketir64thenplusplusne();
extern "C" UINT64 testirsztobracketir64thenplusplusne2();
extern "C" UINT64 testirsztobracketir64thenplusplusnf();
extern "C" UINT64 testirsztobracketir64thenplusplusnf2();
extern "C" UINT64 testirsztobracketir64thenplusplusng();
extern "C" UINT64 testirsztobracketir64thenplusplusng2();
extern "C" UINT64 testirsztobracketir64thenplusplusnh();
extern "C" UINT64 testirsztobracketir64thenplusplusnh2();

extern "C" UINT64 testbracketrspplusntoirsza();
extern "C" UINT64 testirsztobracketrspplusna();

extern "C" UINT64 testmatoscratchreg2sza();
extern "C" UINT64 testmatoscratchreg2szb();
extern "C" UINT64 testmatoscratchreg2szc();
extern "C" UINT64 testmatoscratchreg2szd();
extern "C" UINT64 testmatoscratchreg2sze();
extern "C" UINT64 testmatoscratchreg2szf();
extern "C" UINT64 testmatoscratchreg2szg();
extern "C" UINT64 testmatoscratchreg2szh();
extern "C" UINT64 testmatoscratchreg2szh2();
extern "C" UINT64 testmatoscratchreg2szi();
extern "C" UINT64 testmatoscratchreg2szi2();
extern "C" UINT64 testmbtoscratchreg1sza();
extern "C" UINT64 testmbtoscratchreg1szb();
extern "C" UINT64 testmbtoscratchreg1sza();
extern "C" UINT64 testmbtoscratchreg1szb();
extern "C" UINT64 testmbtoscratchreg1szc();
extern "C" UINT64 testmbtoscratchreg1szd();
extern "C" UINT64 testmbtoscratchreg1sze();
extern "C" UINT64 testmbtoscratchreg1szf();
extern "C" UINT64 testmbtoscratchreg1szg();
extern "C" UINT64 testmbtoscratchreg1szh();
extern "C" UINT64 testmbtoscratchreg1szh2();
extern "C" UINT64 testmbtoscratchreg1szi();
extern "C" UINT64 testmbtoscratchreg1szi2();
extern "C" UINT64 testscratchreg2sztomdesta();
extern "C" UINT64 testscratchreg2sztomdestb();
extern "C" UINT64 testscratchreg2sztomdestc();
extern "C" UINT64 testscratchreg2sztomdestd();
extern "C" UINT64 testscratchreg2sztomdestd2();
extern "C" UINT64 testscratchreg2sztomdeste();
extern "C" UINT64 testscratchreg2sztomdeste2();

extern "C" UINT64 testbracketr8bitrtoraddcomma();
extern "C" UINT64 testrbracketr8bittoraddcomma();
extern "C" UINT64 testrrtobracketr8bitaddcomma();

extern "C" UINT64 test0negcomma();
extern "C" UINT64 test1negcomma();
extern "C" UINT64 test0notcomma();
extern "C" UINT64 test1notcomma();
extern "C" UINT64 test0inccomma();
extern "C" UINT64 test1inccomma();
extern "C" UINT64 test0deccomma();
extern "C" UINT64 test1deccomma();
extern "C" UINT64 testmovcommaa();
extern "C" UINT64 testmovcommab();
extern "C" UINT64 testmovcommac();
extern "C" UINT64 testmovcommad();
extern "C" UINT64 testmovcommae();
extern "C" UINT64 testmovcommaf();
extern "C" UINT64 testmovcommag();
extern "C" UINT64 testmovcommah();
extern "C" UINT64 testmovcommai();
extern "C" UINT64 testmovcommaj();
extern "C" UINT64 testmovcommak();
extern "C" UINT64 testmovcommal();
extern "C" UINT64 testmovcommam();
extern "C" UINT64 testmovcomman();
extern "C" UINT64 testmovcommao();

extern "C" UINT64 testirsztoir64a();
extern "C" UINT64 testirsztoir64b();
extern "C" UINT64 testirsztoir64c();
extern "C" UINT64 testirsztoir64d();
extern "C" UINT64 testirsztoir64e();
extern "C" UINT64 testirsztoir64f();
extern "C" UINT64 testirsztoir64g();
extern "C" UINT64 testirsztoir64h();
extern "C" UINT64 testirsztoir64i();
extern "C" UINT64 testirsztoir64j();

extern "C" UINT64 testr8bitntoraddcomma();
extern "C" UINT64 testnr16bittoraddcomma();
extern "C" UINT64 testnrtor32bitaddcomma();

extern "C" UINT64 testtstcommaa();
extern "C" UINT64 testtstcommab();
extern "C" UINT64 testtstcommac();

extern "C" UINT64 testcmpcommaa();
extern "C" UINT64 testcmpcommab();
extern "C" UINT64 testcmpcommac();
extern "C" UINT64 testcmpcommad();
extern "C" UINT64 testcmpcommae();
extern "C" UINT64 testcmpcommaf();
extern "C" UINT64 testcmpcommag();
extern "C" UINT64 testcmpcommah();
extern "C" UINT64 testcmpcommai();

extern "C" UINT64 testaddcommaai();
extern "C" UINT64 testaddcommaaj();
extern "C" UINT64 testaddcommaak();
extern "C" UINT64 testaddcommaal();

extern "C" UINT64 testarmadccommaa();
extern "C" UINT64 testarmadccommab();

extern "C" UINT64 testarmadcscommaa();
extern "C" UINT64 testarmadcscommab();
extern "C" UINT64 testarmadcscommac();

extern "C" UINT64 testarmcascommaa();
extern "C" UINT64 testarmcascommab();
extern "C" UINT64 testarmcascommac();
extern "C" UINT64 testarmcasacommaa();
extern "C" UINT64 testarmcasacommab();
extern "C" UINT64 testarmcasalcommaa();
extern "C" UINT64 testarmcasalcommab();
extern "C" UINT64 testarmcaslcommaa();
extern "C" UINT64 testarmcaslcommab();

extern "C" UINT64 testarmcaspcommaa();
extern "C" UINT64 testarmcaspcommab();
extern "C" UINT64 testarmcaspcommac();
extern "C" UINT64 testarmcaspcommad();
extern "C" UINT64 testarmcaspcommae();

extern "C" UINT64 testarmcaspacommaa();
extern "C" UINT64 testarmcaspacommab();
extern "C" UINT64 testarmcaspacommac();
extern "C" UINT64 testarmcaspacommad();
extern "C" UINT64 testarmcaspacommae();

extern "C" UINT64 testarmcaspalcommaa();
extern "C" UINT64 testarmcaspalcommab();
extern "C" UINT64 testarmcaspalcommac();
extern "C" UINT64 testarmcaspalcommad();
extern "C" UINT64 testarmcaspalcommae();

extern "C" UINT64 testarmcasplcommaa();
extern "C" UINT64 testarmcasplcommab();
extern "C" UINT64 testarmcasplcommac();
extern "C" UINT64 testarmcasplcommad();
extern "C" UINT64 testarmcasplcommae();

extern "C" UINT64 testarmcasptcommaa();
extern "C" UINT64 testarmcaspatcommaa();
extern "C" UINT64 testarmcaspaltcommaa();
extern "C" UINT64 testarmcaspltcommaa();

extern "C" UINT64 testarmcsetcommaa();
extern "C" UINT64 testarmcsetcommab();
extern "C" UINT64 testarmcsetmcommaa();
extern "C" UINT64 testarmcsetmcommab();

extern "C" UINT64 testarmcselcommaa();
extern "C" UINT64 testarmcselcommab();

extern "C" UINT64 testarmcntcommaa();
extern "C" UINT64 testarmcntcommab();

extern "C" UINT64 testarmclscommaa();
extern "C" UINT64 testarmclscommab();
extern "C" UINT64 testarmclscommac();
extern "C" UINT64 testarmclscommad();

extern "C" UINT64 testarmclzcommaa();
extern "C" UINT64 testarmclzcommab();
extern "C" UINT64 testarmclzcommac();

extern "C" UINT64 testarmrbitcommaa();
extern "C" UINT64 testarmrevcommaa();
extern "C" UINT64 testarmrev64commaa();
extern "C" UINT64 testarmrev32commaa();
extern "C" UINT64 testarmrev16commaa();

extern "C" UINT64 testarmldxpcommaa();
extern "C" UINT64 testarmldxpcommab();
extern "C" UINT64 testarmstxpcommaa();
extern "C" UINT64 testarmstxpcommab();
extern "C" UINT64 testarmstxpcommac();
extern "C" UINT64 testarmstxpcommad();

extern "C" UINT64 testarmldpcommaa();
extern "C" UINT64 testarmldpcommab();
extern "C" UINT64 testarmldpcommac();
extern "C" UINT64 testarmldpcommad();
extern "C" UINT64 testarmldpimmpluspluscommaa();
extern "C" UINT64 testarmldpimmpluspluscommab();
extern "C" UINT64 testarmldpimmpluspluscommac();

extern "C" UINT64 testarmcsinca();
extern "C" UINT64 testarmcsincb();
extern "C" UINT64 testarmcsinva();
extern "C" UINT64 testarmcsinvb();
extern "C" UINT64 testarmcsnega();
extern "C" UINT64 testarmcsnegb();

extern "C" UINT64 testarmcinca();
extern "C" UINT64 testarmcincb();
extern "C" UINT64 testarmcinva();
extern "C" UINT64 testarmcinvb();
extern "C" UINT64 testarmcnega();
extern "C" UINT64 testarmcnegb();

extern "C" UINT64 testarmldaddcommaa();
extern "C" UINT64 testarmldaddcommab();
extern "C" UINT64 testarmldaddcommac();
extern "C" UINT64 testarmldaddcommad();
extern "C" UINT64 testarmldaddcommae();
extern "C" UINT64 testarmldaddcommaf();
extern "C" UINT64 testarmldaddcommag();

extern "C" UINT64 testarmimmplusplusldpcommaa();
extern "C" UINT64 testarmimmplusplusldpcommab();
extern "C" UINT64 testarmimmplusplusldpcommac();

extern "C" UINT64 testarmandsimmcommaa();
extern "C" UINT64 testarmandsimmcommab();
extern "C" UINT64 testarmandsimmcommac();
extern "C" UINT64 testarmandsimmcommad();

extern "C" UINT64 testarmbfccomma();
extern "C" UINT64 testarmbficomma();
extern "C" UINT64 testarmbfmcomma();
extern "C" UINT64 testarmbfxilcomma();

extern "C" UINT64 testarmcbimmcommaa();
extern "C" UINT64 testarmcbimmcommab();
extern "C" UINT64 testarmcbimmcommac();
extern "C" UINT64 testarmcbimmcommad();
extern "C" UINT64 testarmcbimmcommae();
extern "C" UINT64 testarmcbimmcommaf();

extern "C" UINT64 testarmmrsregcommaa();
extern "C" UINT64 testarmmrsregcommab();
extern "C" UINT64 testarmmrsregcommac();
extern "C" UINT64 testarmmsrregcommaa();
extern "C" UINT64 testarmmsrregcommab();
extern "C" UINT64 testarmmsrregcommac();
extern "C" UINT64 testarmmsrcommaa();
extern "C" UINT64 testarmmrscommaa();

extern "C" UINT64 testarmccmnimmcommaaa();
extern "C" UINT64 testarmccmnimmcommaab();
extern "C" UINT64 testarmccmnimmcommaac();
extern "C" UINT64 testarmccmnimmcommaad();
extern "C" UINT64 testarmccmnimmcommaae();
extern "C" UINT64 testarmccmnimmcommaaf();
extern "C" UINT64 testarmccmnimmcommaag();
extern "C" UINT64 testarmccmnimmcommaah();
extern "C" UINT64 testarmccmnimmcommaai();
extern "C" UINT64 testarmccmnimmcommaaj();
extern "C" UINT64 testarmccmnimmcommaak();

extern "C" UINT64 testarmccmnimmcommaba();
extern "C" UINT64 testarmccmnimmcommabb();
extern "C" UINT64 testarmccmnimmcommabc();

extern "C" UINT64 testarmccmnimmcommaa();
extern "C" UINT64 testarmccmnimmcommaf();
extern "C" UINT64 testarmccmnimmcommag();
extern "C" UINT64 testarmccmnimmcommah();
extern "C" UINT64 testarmccmnimmcommab();
extern "C" UINT64 testarmccmnimmcommac();
extern "C" UINT64 testarmccmnimmcommad();
extern "C" UINT64 testarmccmnimmcommae();
extern "C" UINT64 testarmccmnregcommaa();
extern "C" UINT64 testarmccmpimmcommaa();
extern "C" UINT64 testarmccmpimmcommab();
extern "C" UINT64 testarmccmpregcommaa();
extern "C" UINT64 testarmccmpregcommab();

extern "C" UINT64 testarmcpyfpcommaa();

extern "C" UINT64 testarmcrc32bcommaa();
extern "C" UINT64 testarmcrc32bcommab();

extern "C" UINT64 testarmextrcommaa();

// extern "C" UINT64 testarmrcwcascommaa();
// extern "C" UINT64 testarmrcwcascommab();

extern "C" UINT64 testarmrmifcommaa();
extern "C" UINT64 testarmrmifcommab();

extern "C" UINT64 testarmrorimmcommaa();
extern "C" UINT64 testarmrolimmcommaa();
extern "C" UINT64 testarmrorregcommaa();

extern "C" UINT64 testarmsetf8commaa();
extern "C" UINT64 testarmsetf8commab();
extern "C" UINT64 testarmsetf16commaa();
extern "C" UINT64 testarmsetf16commab();

extern "C" UINT64 testarmsmneglcommaa();
extern "C" UINT64 testarmstlpcommaa();
extern "C" UINT64 testarmstlpcommab();

extern "C" UINT64 testarmtbnzcommaa();
extern "C" UINT64 testarmtbnzcommab();
extern "C" UINT64 testarmtbnzcommac();
extern "C" UINT64 testarmtbnzcommad();

extern "C" UINT64 testarmtbzcommaa();
extern "C" UINT64 testarmtbzcommab();
extern "C" UINT64 testarmtbzcommac();
extern "C" UINT64 testarmtbzcommad();

extern "C" UINT64 testarmmulcommaa();

extern "C" UINT64 testarmmvncommaa();
extern "C" UINT64 testarmmvncommab();
extern "C" UINT64 testarmmvncommac();

extern "C" UINT64 testarmnegcommaa();
extern "C" UINT64 testarmnegcommab();
extern "C" UINT64 testarmnegcommac();

extern "C" UINT64 testarmnegscommaa();
extern "C" UINT64 testarmnegscommab();
extern "C" UINT64 testarmnegscommac();
extern "C" UINT64 testarmnegscommad();
extern "C" UINT64 testarmnegscommae();

extern "C" UINT64 testarmmovbitmaskimma();

extern "C" UINT64 testarmstpcommaa();
extern "C" UINT64 testarmstpcommab();
extern "C" UINT64 testarmstpimmpluspluscommaa();
extern "C" UINT64 testarmstpimmpluspluscommab();
extern "C" UINT64 testarmstpimmpluspluscommac();
extern "C" UINT64 testarmimmplusplusstpcommaa();
extern "C" UINT64 testarmimmplusplusstpcommab();
extern "C" UINT64 testarmimmplusplusstpcommac();

extern "C" UINT64 testarmldclrcommaa();
extern "C" UINT64 testarmldclrcommab();
extern "C" UINT64 testarmldeorcommaa();
extern "C" UINT64 testarmldeorcommab();
extern "C" UINT64 testarmldsetcommaa();
extern "C" UINT64 testarmldsetcommab();

extern "C" UINT64 testarmldsmaxcommaa();
extern "C" UINT64 testarmldsmaxcommab();
extern "C" UINT64 testarmldsmaxcommac();
extern "C" UINT64 testarmldsmaxcommad();

extern "C" UINT64 testarmldsmincommaa();
extern "C" UINT64 testarmldsmincommab();
extern "C" UINT64 testarmldsmincommac();
extern "C" UINT64 testarmldsmincommad();

extern "C" UINT64 testarmldumaxcommaa();
extern "C" UINT64 testarmldumaxcommab();
extern "C" UINT64 testarmldumaxcommac();
extern "C" UINT64 testarmldumaxcommad();

extern "C" UINT64 testarmldumincommaa();
extern "C" UINT64 testarmldumincommab();
extern "C" UINT64 testarmldumincommac();
extern "C" UINT64 testarmldumincommad();

extern "C" UINT64 testarmstaddcommaa();

extern "C" UINT64 testarmswpcommaa();
extern "C" UINT64 testarmswpcommab();

extern "C" UINT64 testarmldarbcommaa();

extern "C" UINT64 testarmsxtbcommaa();
extern "C" UINT64 testarmsxtbcommab();
extern "C" UINT64 testarmsxthcommaa();
extern "C" UINT64 testarmsxthcommab();

extern "C" UINT64 testarmsbfxcommaa();
extern "C" UINT64 testarmsbfizcommaa();

extern "C" UINT64 testarmngccommaa();
extern "C" UINT64 testarmngccommab();

extern "C" UINT64 testarmngcscommaa();
extern "C" UINT64 testarmngcscommab();
extern "C" UINT64 testarmngcscommac();
extern "C" UINT64 testarmngcscommad();

extern "C" UINT64 testarmsbccommaa();
extern "C" UINT64 testarmsbccommab();

extern "C" UINT64 testarmsbcscommaa();
extern "C" UINT64 testarmsbcscommab();
extern "C" UINT64 testarmsbcscommac();

extern "C" UINT64 testarmmsubcommaa();
extern "C" UINT64 testarmsmaddlcommaa();
extern "C" UINT64 testarmsmsublcommaa();
extern "C" UINT64 testarmumaddlcommaa();
extern "C" UINT64 testarmumsublcommaa();

extern "C" UINT64 testarmsmullcommaa();
extern "C" UINT64 testarmsmullcommab();
extern "C" UINT64 testarmsmulhcommaa();
extern "C" UINT64 testarmsmulhcommab();
extern "C" UINT64 testarmumullcommaa();
extern "C" UINT64 testarmumullcommab();

extern "C" UINT64 testarmsxtwcommaa();
extern "C" UINT64 testarmuxtbcommaa();
extern "C" UINT64 testarmuxthcommaa();

extern "C" UINT64 testarmbrcommaa();
extern "C" UINT64 testarmblrcommaa();

extern "C" UINT64 testarmmnegcommaa();
extern "C" UINT64 testarmumneglcommaa();

extern "C" UINT64 testarmubfizcommaa();
extern "C" UINT64 testarmubfxcommaa();

// extern "C" UINT64 testarmsmaxrega();
// extern "C" UINT64 testarmsmaxregb();
// extern "C" UINT64 testarmsminrega();
// extern "C" UINT64 testarmsminregb();

int main(int argc, char* argv[])
{
    UINT64 x, y, ptestconstant1;
    UINT64 startingrsp;

    startingrsp = getrsp();

    printf("testing testexp.o\n");
    

    printf("  testing testarmret\n");

    x = testarmret();

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }


    printf("  testing testarmnop\n");

    x = testarmnop();


    printf("  testing testarmmovz1\n");

    x = testarmmovz1();
    
    if (x != 0x1234ULL)
    {
    
       printf("  FAIL! testarmmovz1() success test - expected 0x1234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovz2\n");

    x = testarmmovz2();
    
    if (x != 0x12340000ULL)
    {
    
       printf("  FAIL! testarmmovz2() success test - expected 0x12340000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovz3\n");

    x = testarmmovz3();
    
    if (x != 0x123400000000ULL)
    {
    
       printf("  FAIL! testarmmovz3() success test - expected 0x123400000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovz4\n");

    x = testarmmovz4();
    
    if (x != 0x1234000000000000ULL)
    {
    
       printf("  FAIL! testarmmovz4() success test - expected 0x1234000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovk1\n");

    x = testarmmovk1();
    
    if (x != 0x0011667744552233ULL)
    {
    
       printf("  FAIL! testarmmovk1() success test - expected 0x0011667744552233, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovr1\n");

    x = testarmmovr1(0x1234567877665544ULL);
    
    if (x != 0x1234567877665544)
    {
    
       printf("  FAIL! testarmmovr1() success test - expected 0x1234567877665544, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovr2\n");

    x = testarmmovr2();
    
    if (x != 0x0011667744552233ULL)
    {
    
       printf("  FAIL! testarmmovr2() success test - expected 0x0011667744552233, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovn1\n");

    x = testarmmovn1();
    
    if (x != 0xFFFFFFFFFFFFEDCBULL)
    {
    
       printf("  FAIL! testarmmovn1() success test - expected 0xFFFFFFFFFFFFEDCB, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovn2\n");

    x = testarmmovn2();
    
    if (x != 0xFFFFFFFFEDCBFFFFULL)
    {
    
       printf("  FAIL! testarmmovn2() success test - expected 0xFFFFFFFFEDCBFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovn3\n");

    x = testarmmovn3();
    
    if (x != 0xFFFFEDCBFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmmovn3() success test - expected 0xFFFFEDCBFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmovn4\n");

    x = testarmmovn4();
    
    if (x != 0xEDCBFFFFFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmmovn4() success test - expected 0xEDCBFFFFFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovn5\n");

    x = testarmmovn5();
    
    if (x != 0xFFFFFFFFFFFFEDCBULL)
    {
    
       printf("  FAIL! testarmmovn4() success test - expected 0xFFFFFFFFFFFFEDCB, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate1\n");

    x = testarmaddimmediate1();
    
    if (x != 0x000000000000179BULL)
    {
    
       printf("  FAIL! testarmaddimmediate1() success test - expected 0x000000000000179B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate2\n");

    x = testarmaddimmediate2();
    
    if (x != 0x0000000000568234ULL)
    {
    
       printf("  FAIL! testarmaddimmediate2() success test - expected 0x0000000000568234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate3\n");

    x = testarmaddimmediate3();
    
    if (x != 0x0000000000568235ULL)
    {
    
       printf("  FAIL! testarmaddimmediate3() success test - expected 0x0000000000568235, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate4\n");

    x = testarmaddimmediate4();
    
    if (x != 0x1235000000567000ULL)
    {
    
       printf("  FAIL! testarmaddimmediate4() success test - expected 0x1235000000567000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate5\n");

    x = testarmaddimmediate5();
    
    if (x != 0x1236000000567000ULL)
    {
    
       printf("  FAIL! testarmaddimmediate5() success test - expected 0x1236000000567000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate6\n");

    x = testarmaddimmediate6();
    
    if (x != 0x1237000000567000ULL)
    {
    
       printf("  FAIL! testarmaddimmediate6() success test - expected 0x1237000000567000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb1\n");

    x = testarmb1();
    
    if (x != 0x1133ULL)
    {
    
       printf("  FAIL! testarmb1() success test - expected 0x1133, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb2\n");

    x = testarmb2();
    
    if (x != 0x1122ULL)
    {
    
       printf("  FAIL! testarmb1() success test - expected 0x1122, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond1\n");

    x = testarmbdotcond1();
    
    if (x != 0x1155ULL)
    {
    
       printf("  FAIL! testarmb.cond1() success test - expected 0x1155, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond2\n");

    x = testarmbdotcond2();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testarmb.cond2() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddimmediate7\n");

    x = testarmaddimmediate7();
    
    if (x != 0x1166ULL)
    {
    
       printf("  FAIL! testarmaddimmediate7() success test - expected 0x1166, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond3\n");

    x = testarmbdotcond3();
    
    if (x != 0x1177ULL)
    {
    
       printf("  FAIL! testarmb.cond3() success test - expected 0x1177, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond4\n");

    x = testarmbdotcond4();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmb.cond4() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond5\n");

    x = testarmbdotcond5();
    
    if (x != 0x7fffffffffffffffULL)
    {
    
       printf("  FAIL! testarmb.cond5() success test - expected 0x7fffffffffffffff, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond6\n");

    x = testarmbdotcond6();
    
    if (x != 0x1188ULL)
    {
    
       printf("  FAIL! testarmb.cond6() success test - expected 0x1188, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond7\n");

    x = testarmbdotcond7();
    
    if (x != 0x1199ULL)
    {
    
       printf("  FAIL! testarmb.cond7() success test - expected 0x1199, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond8\n");

    x = testarmbdotcond8();
    
    if (x != 0xffffffffffffffffULL)
    {
    
       printf("  FAIL! testarmb.cond8() success test - expected 0xffffffffffffffff, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond9\n");

    x = testarmbdotcond9();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testarmb.cond9() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond10\n");

    x = testarmbdotcond10();
    
    if (x != 0x2211ULL)
    {
    
       printf("  FAIL! testarmb.cond10() success test - expected 0x2211, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond11\n");

    x = testarmbdotcond11();
    
    if (x != 0x2222ULL)
    {
    
       printf("  FAIL! testarmb.cond11() success test - expected 0x2222, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmb.cond12\n");

    x = testarmbdotcond12();
    
    if (x != 0x2223ULL)
    {
    
       printf("  FAIL! testarmb.cond12() success test - expected 0x2223, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmneifcomma\n");

    x = testarmneifcomma();
    
    if (x != 0x2224ULL)
    {
    
       printf("  FAIL! testarmneifcomma() success test - expected 0x2224, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmeqifcomma\n");

    x = testarmeqifcomma();
    
    if (x != 0x2225ULL)
    {
    
       printf("  FAIL! testarmeqifcomma() success test - expected 0x2225, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmeqifelsecomma\n");

    x = testarmeqifelsecomma();
    
    if (x != 0x2226ULL)
    {
    
       printf("  FAIL! testarmeqifelsecomma() success test - expected 0x2226, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbeginequntilcomma\n");

    x = testarmbeginequntilcomma();
    
    if (x != 0x10ULL)
    {
    
       printf("  FAIL! testarmbeginequntilcomma() success test - expected 0x10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbeginnewhilerepeatcomma\n");

    x = testarmbeginnewhilerepeatcomma();
    
    if (x != 0x0CULL)
    {
    
       printf("  FAIL! testarmbeginnewhilerepeatcomma() success test - expected 0x0C, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate1\n");

    x = testarmsubimmediate1();
    
    if (x != 0x000000000000CCDULL)
    {
    
       printf("  FAIL! testarmsubimmediate1() success test - expected 0x000000000000CCD, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate2\n");

    x = testarmsubimmediate2();
    
    if (x != 0xFFFFFFFFFFA9A234ULL)
    {
    
       printf("  FAIL! testarmsubimmediate2() success test - expected 0xFFFFFFFFFA991234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate3\n");

    x = testarmsubimmediate3();
    
    if (x != 0xFFFFFFFFFFA9A235ULL)
    {
    
       printf("  FAIL! testarmsubimmediate3() success test - expected 0xFFFFFFFFFFA9A235, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate4\n");

    x = testarmsubimmediate4();
    
    if (x != 0x1234FFFFFFA99000ULL)
    {
    
       printf("  FAIL! testarmsubimmediate4() success test - expected 0x1234FFFFFFA99000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate5\n");

    x = testarmsubimmediate5();
    
    if (x != 0x1235FFFFFFA99000ULL)
    {
    
       printf("  FAIL! testarmsubimmediate5() success test - expected 0x1235FFFFFFA99000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubimmediate6\n");

    x = testarmsubimmediate6();
    
    if (x != 0x1236FFFFFFA99000ULL)
    {
    
       printf("  FAIL! testarmsubimmediate6() success test - expected 0x1236FFFFFFA99000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended1\n");

    x = testarmaddextended1();
    
    if (x != 0x033BULL)
    {
    
       printf("  FAIL! testarmaddextended1() success test - expected 0x033B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended2\n");

    x = testarmaddextended2();
    
    if (x != 0x0372ULL)
    {
    
       printf("  FAIL! testarmaddextended2() success test - expected 0x0372, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended3\n");

    x = testarmaddextended3();
    
    if (x != 0x03E0ULL)
    {
    
       printf("  FAIL! testarmaddextended3() success test - expected 0x03E0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended4\n");

    x = testarmaddextended4();
    
    if (x != 0x04BCULL)
    {
    
       printf("  FAIL! testarmaddextended4() success test - expected 0x04BC, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended5\n");

    x = testarmaddextended5();
    
    if (x != 0x0674ULL)
    {
    
       printf("  FAIL! testarmaddextended5() success test - expected 0x0674, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended6\n");

    x = testarmaddextended6();
    
    if (x != 0x153BULL)
    {
    
       printf("  FAIL! testarmaddextended6() success test - expected 0x153B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended7\n");

    x = testarmaddextended7();
    
    if (x != 0x2772ULL)
    {
    
       printf("  FAIL! testarmaddextended7() success test - expected 0x2772, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended8\n");

    x = testarmaddextended8();
    
    if (x != 0x5678153BULL)
    {
    
       printf("  FAIL! testarmaddextended8() success test - expected 0x5678153B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddextended9\n");

    x = testarmaddextended9();
    
    if (x != 0x32109ABC5678153BULL)
    {
    
       printf("  FAIL! testarmaddextended9() success test - expected 0x32109ABC5678153B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddsextended1\n");

    x = testarmaddsextended1();
    
    if (x != 0x3912ULL)
    {
    
       printf("  FAIL! testarmaddsextended1() success test - expected 0x3912, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubextended1\n");

    x = testarmsubextended1();
    
    if (x != 0xCDEF6543A987F0CDULL)
    {
    
       printf("  FAIL! testarmsubextended1() success test - expected 0xCDEF6543A987F0CD, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubsextended1\n");

    x = testarmsubsextended1();
    
    if (x != 0x3913ULL)
    {
    
       printf("  FAIL! testarmsubsextended1() success test - expected 0x3913, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpextended1\n");

    x = testarmcmpextended1();
    
    if (x != 0x3914ULL)
    {
    
       printf("  FAIL! testarmcmpextended1() success test - expected 0x3914, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpextended2\n");

    x = testarmcmpextended2();
    
    if (x != 0x3ULL)
    {
    
       printf("  FAIL! testarmcmpextended2() success test - expected 0x3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnextended1\n");

    x = testarmcmnextended1();
    
    if (x != 0x3917ULL)
    {
    
       printf("  FAIL! testarmcmnextended1() success test - expected 0x3917, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnextended2\n");

    x = testarmcmnextended2();
    
    if (x != 0x5ULL)
    {
    
       printf("  FAIL! testarmcmnextended2() success test - expected 0x5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
/*
    printf("  testing testarmabs1\n");

    x = testarmabs1();
    
    if (x != 0x7ULL)
    {
    
       printf("  FAIL! testarmabs1() success test - expected 0x7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmabs2\n");

    x = testarmabs2();
    
    if (x != 0x6ULL)
    {
    
       printf("  FAIL! testarmabs2() success test - expected 0x6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/

    printf("  testing testarmaddshiftedreg1\n");

    x = testarmaddshiftedreg1();
    
    if (x != 0x8ULL)
    {
    
       printf("  FAIL! testarmaddshiftedreg1() success test - expected 0x8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddshiftedreg2\n");

    x = testarmaddshiftedreg2();
    
    if (x != 0x0DULL)
    {
    
       printf("  FAIL! testarmaddshiftedreg2() success test - expected 0x0D, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddshiftedreg3\n");

    x = testarmaddshiftedreg3();
    
    if (x != 0x5000000000000000ULL)
    {
    
       printf("  FAIL! testarmaddshiftedreg3() success test - expected 0x5000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddshiftedreg4\n");

    x = testarmaddshiftedreg4();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testarmaddshiftedreg4() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmaddsshiftedreg1\n");

    x = testarmaddsshiftedreg1();
    
    if (x != 0x1267ULL)
    {
    
       printf("  FAIL! testarmaddsshiftedreg1() success test - expected 0x1267, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandshiftedreg1\n");

    x = testarmandshiftedreg1();
    
    if (x != 0x1111000000000000ULL)
    {
    
       printf("  FAIL! testarmandshiftedreg1() success test - expected 0x1111000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbicshiftedreg1\n");

    x = testarmbicshiftedreg1();
    
    if (x != 0x4444000000000000ULL)
    {
    
       printf("  FAIL! testarmbicshiftedreg1() success test - expected 0x4444000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmorrshiftedreg1\n");

    x = testarmorrshiftedreg1();
    
    if (x != 0x7777000000000000ULL)
    {
    
       printf("  FAIL! testarmorrrshiftedreg1() success test - expected 0x7777000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmornshiftedreg1\n");

    x = testarmornshiftedreg1();
    
    if (x != 0xDDDDFFFFFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmornshiftedreg1() success test - expected 0xDDDDFFFFFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmeorshiftedreg1\n");

    x = testarmeorshiftedreg1();
    
    if (x != 0x6666000000000000ULL)
    {
    
       printf("  FAIL! testarmeorshiftedreg1() success test - expected 0x6666000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmeonshiftedreg1\n");

    x = testarmeonshiftedreg1();
    
    if (x != 0x9999FFFFFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmeonshiftedreg1() success test - expected 0x9999FFFFFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubshiftedreg1\n");

    x = testarmsubshiftedreg1();
    
    if (x != 0x7000000000000000ULL)
    {
    
       printf("  FAIL! testarmsubshiftedreg1() success test - expected 0x7000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubsshiftedreg1\n");

    x = testarmsubsshiftedreg1();
    
    if (x != 0x9217ULL)
    {
    
       printf("  FAIL! testarmsubsshiftedreg1() success test - expected 0x9217, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsubsimmediate1\n");

    x = testarmsubsimmediate1();
    
    if (x != 0x9001ULL)
    {
    
       printf("  FAIL! testarmsubsimmediate1() success test - expected 0x9001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpimmediate1\n");

    x = testarmcmpimmediate1();
    
    if (x != 0x9966ULL)
    {
    
       printf("  FAIL! testarmcmpimmediate1() success test - expected 0x9966, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpimmediate2\n");

    x = testarmcmpimmediate2();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testarmcmpimmediate2() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpimmediate3\n");

    x = testarmcmpimmediate3();
    
    if (x != 0x9968ULL)
    {
    
       printf("  FAIL! testarmcmpimmediate3() success test - expected 0x9968, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnimmediate1\n");

    x = testarmcmnimmediate1();
    
    if (x != 0x9968ULL)
    {
    
       printf("  FAIL! testarmcmnimmediate1() success test - expected 0x9968, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnimmediate2\n");

    x = testarmcmnimmediate2();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testarmcmnimmediate2() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnimmediate3\n");

    x = testarmcmnimmediate3();
    
    if (x != 0x9970ULL)
    {
    
       printf("  FAIL! testarmcmnimmediate3() success test - expected 0x9970, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnshiftedreg1\n");

    x = testarmcmnshiftedreg1();
    
    if (x != 0x3267ULL)
    {
    
       printf("  FAIL! testarmcmnshiftedreg1() success test - expected 0x3267, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmnshiftedreg2\n");

    x = testarmcmnshiftedreg2();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testarmcmnshiftedreg2() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsshiftedreg1\n");

    x = testarmandsshiftedreg1();
    
    if (x != 0x1298ULL)
    {
    
       printf("  FAIL! testarmandsshiftedreg1() success test - expected 0x1298, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsshiftedreg2\n");

    x = testarmandsshiftedreg2();
    
    if (x != 0x8ULL)
    {
    
       printf("  FAIL! testarmandsshiftedreg2() success test - expected 0x8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbicsshiftedreg1\n");

    x = testarmbicsshiftedreg1();
    
    if (x != 0x9274ULL)
    {
    
       printf("  FAIL! testarmbicsshiftedreg1() success test - expected 0x9274, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbicsshiftedreg2\n");

    x = testarmbicsshiftedreg2();
    
    if (x != 0x4ULL)
    {
    
       printf("  FAIL! testarmbicsshiftedreg2() success test - expected 0x4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpshiftedreg1\n");

    x = testarmcmpshiftedreg1();
    
    if (x != 0x9257ULL)
    {
    
       printf("  FAIL! testarmcmpshiftedreg1() success test - expected 0x9257, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcmpshiftedreg2\n");

    x = testarmcmpshiftedreg2();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmcmpshiftedreg2() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtstshiftedreg1\n");

    x = testarmtstshiftedreg1();
    
    if (x != 0x9357ULL)
    {
    
       printf("  FAIL! testarmtstshiftedreg1() success test - expected 0x9357, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtstshiftedreg2\n");

    x = testarmtstshiftedreg2();
    
    if (x != 0x10ULL)
    {
    
       printf("  FAIL! testarmtstshiftedreg2() success test - expected 0x10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrlit1\n");

    x = testarmldrlit1();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmldrlit1() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrlit2\n");

    x = testarmldrlit2();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmldrlit2() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrlit3\n");

    x = testarmldrlit3();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmldrlit3() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadrarmldrimm1\n");

    x = testarmadrarmldrimm1();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmadrarmldrimm1() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadrarmldrimm2\n");

    x = testarmadrarmldrimm2();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testarmadrarmldrimm2() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadrarmldrimm3\n");

    x = testarmadrarmldrimm3();
    
    if (x != 0x8182838485868788ULL)
    {
    
       printf("  FAIL! testarmadrarmldrimm3() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrimmplusplus1\n");

    x = testarmldrimmplusplus1();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmldrimmplusplus1() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrimmplusplus2\n");

    x = testarmldrimmplusplus2();
    ptestconstant1 = getptestconstant1();
    x = x - ptestconstant1;
    
    if (x != 8ULL)
    {
    
       printf("  FAIL! testarmldrimmplusplus2() success test - expected 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldr1\n");

    x = testarmimmplusplusldr1();
    
    if (x != 0x8182838485868788ULL)
    {
    
       printf("  FAIL! testarmimmplusplusldr1() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldr2\n");

    x = testarmimmplusplusldr2();
    x = x - ptestconstant1;
    
    if (x != 0x10ULL)
    {
    
       printf("  FAIL! testarmimmplusplusldr2() success test - expected 0x10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldr3\n");

    x = testarmimmplusplusldr3();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmimmplusplusldr3() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg1\n");

    x = testarmldrreg1();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testarmldrreg1() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg1\n");

    x = testarmldrreg2();
    
    if (x != 0x8182838485868788ULL)
    {
    
       printf("  FAIL! testarmldrreg2() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg3\n");

    x = testarmldrreg3();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testarmldrreg3() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg4\n");

    x = testarmldrreg4();
    
    if (x != 0x8182838485868788ULL)
    {
    
       printf("  FAIL! testarmldrreg4() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg5\n");

    x = testarmldrreg5();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testarmldrreg5() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrreg6\n");

    x = testarmldrreg6();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testarmldrreg6() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovsp1\n");

    x = testarmmovsp1();
    
    if (x != 0x8ULL)
    {
    
       printf("  FAIL! testarmmovsp1() success test - expected 0x8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }


    printf("  testing testarmpushsp1\n");

    x = testarmpushsp1();
    
    if (x != 0x1352ULL)
    {
    
       printf("  FAIL! testarmpushsp1() success test - expected 0x1352, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmpushsp2\n");

    x = testarmpushsp2();
    
    if (x != 0x7994ULL)
    {
    
       printf("  FAIL! testarmpushsp2() success test - expected 0x7994, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmpopsp1\n");

    x = testarmpopsp1();
    
    if (x != 0x5239ULL)
    {
    
       printf("  FAIL! testarmpopsp1() success test - expected 0x5239, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmpopsp2\n");

    x = testarmpopsp2();
    
    if (x != 0x8647ULL)
    {
    
       printf("  FAIL! testarmpopsp2() success test - expected 0x8647, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm1\n");

    x = testarmstrimm1();
    
    if (x != 0x1537ULL)
    {
    
       printf("  FAIL! testarmstrimm1() success test - expected 0x1537, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm2\n");

    x = testarmstrimm2();
    
    if (x != 0x2398ULL)
    {
    
       printf("  FAIL! testarmstrimm2() success test - expected 0x2398, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm3\n");

    x = testarmstrimm3();
    
    if (x != 0x1637ULL)
    {
    
       printf("  FAIL! testarmstrimm3() success test - expected 0x1637, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm4\n");

    x = testarmstrimm4();
    
    if (x != 0x1284ULL)
    {
    
       printf("  FAIL! testarmstrimm4() success test - expected 0x1284, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm5\n");

    x = testarmstrimm5();
    
    if (x != 0x8742ULL)
    {
    
       printf("  FAIL! testarmstrimm5() success test - expected 0x8742, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmstrimm6\n");

    x = testarmstrimm6();
    
    if (x != 0x10ULL)
    {
    
       printf("  FAIL! testarmstrimm6() success test - expected 0x10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

    printf("  testing testarmsbfm1\n");

    x = testarmsbfm1();
    
    if (x != 0xDEF09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmsbfm1() success test - expected 0xDEF09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfm2\n");

    x = testarmsbfm2();
    
    if (x != 0xFDEF09ABC5678123ULL)
    {
    
       printf("  FAIL! testarmsbfm2() success test - expected 0xFDEF09ABC5678123, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfm3\n");

    x = testarmsbfm3();
    
    if (x != 0xFFDEF09ABC567812ULL)
    {
    
       printf("  FAIL! testarmsbfm3() success test - expected 0xFFDEF09ABC567812, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfm4\n");

    x = testarmsbfm4();
    
    if (x != 0xFEF09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmsbfm4() success test - expected 0xFEF09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfm5\n");

    x = testarmsbfm5();
    
    if (x != 0xFFF09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmsbfm5() success test - expected 0xFFF09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfm6\n");

    x = testarmsbfm6();
    
    if (x != 0xFFEF09ABC5678123ULL)
    {
    
       printf("  FAIL! testarmsbfm6() success test - expected 0xFFEF09ABC5678123, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm1\n");

    x = testarmubfm1();
    
    if (x != 0xDEF09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmubfm1() success test - expected 0xDEF09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm2\n");

    x = testarmubfm2();
    
    if (x != 0x0DEF09ABC5678123ULL)
    {
    
       printf("  FAIL! testarmubfm2() success test - expected 0x0DEF09ABC5678123, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm3\n");

    x = testarmubfm3();
    
    if (x != 0x00DEF09ABC567812ULL)
    {
    
       printf("  FAIL! testarmubfm3() success test - expected 0x00DEF09ABC567812, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm4\n");

    x = testarmubfm4();
    
    if (x != 0x0EF09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmubfm4() success test - expected 0x0EF09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm5\n");

    x = testarmubfm5();
    
    if (x != 0x00F09ABC56781234ULL)
    {
    
       printf("  FAIL! testarmubfm5() success test - expected 0x00F09ABC56781234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfm6\n");

    x = testarmubfm6();
    
    if (x != 0x00EF09ABC5678123ULL)
    {
    
       printf("  FAIL! testarmubfm6() success test - expected 0x00EF09ABC5678123, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmadd1\n");

    x = testarmmadd1();
    
    if (x != 0x26ULL)
    {
    
       printf("  FAIL! testarmmadd1() success test - expected 0x26, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmudiv1\n");

    x = testarmudiv1();
    
    if (x != 0x5ULL)
    {
    
       printf("  FAIL! testarmudiv1() success test - expected 0x5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsdiv1\n");

    x = testarmsdiv1();
    
    if (x != 0x7ULL)
    {
    
       printf("  FAIL! testarmsdiv1() success test - expected 0x7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumulh1\n");

    x = testarmumulh1();
    
    if (x != 0x2ULL)
    {
    
       printf("  FAIL! testarmumulh1() success test - expected 0x2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate1\n");

    x = testarmasrimmediate1();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrimmediate1() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate2\n");

    x = testarmasrimmediate2();
    
    if (x != 0xC000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrimmediate2() success test - expected 0xC000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate3\n");

    x = testarmasrimmediate3();
    
    if (x != 0x2000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrimmediate3() success test - expected 0x2000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate4\n");

    x = testarmasrimmediate4();
    
    if (x != 0xFFFFFFFFFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmasrimmediate4() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate5\n");

    x = testarmasrimmediate5();
    
    if (x != 0xC0000000ULL)
    {
    
       printf("  FAIL! testarmasrimmediate5() success test - expected 0xC0000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate6\n");

    x = testarmasrimmediate6();
    
    if (x != 0x20000000ULL)
    {
    
       printf("  FAIL! testarmasrimmediate6() success test - expected 0x20000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrimmediate7\n");

    x = testarmasrimmediate7();
    
    if (x != 0xFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmasrimmediate7() success test - expected 0xFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate1\n");

    x = testarmlsrimmediate1();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate1() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate2\n");

    x = testarmlsrimmediate2();
    
    if (x != 0x4000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate2() success test - expected 0x4000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate3\n");

    x = testarmlsrimmediate3();
    
    if (x != 0x2000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate3() success test - expected 0x2000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate4\n");

    x = testarmlsrimmediate4();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate4() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate5\n");

    x = testarmlsrimmediate5();
    
    if (x != 0x40000000ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate5() success test - expected 0x40000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate6\n");

    x = testarmlsrimmediate6();
    
    if (x != 0x20000000ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate6() success test - expected 0x20000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrimmediate7\n");

    x = testarmlsrimmediate7();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testarmlsrimmediate7() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslimmediate1\n");

    x = testarmlslimmediate1();
    
    if (x != 0x0000000000000001ULL)
    {
    
       printf("  FAIL! testarmlslimmediate1() success test - expected 0x0000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslimmediate2\n");

    x = testarmlslimmediate2();
    
    if (x != 0x0000000000000002ULL)
    {
    
       printf("  FAIL! testarmlslimmediate2() success test - expected 0x0000000000000002, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslimmediate3\n");

    x = testarmlslimmediate3();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmlslimmediate3() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslimmediate4\n");

    x = testarmlslimmediate4();
    
    if (x != 0x4ULL)
    {
    
       printf("  FAIL! testarmlslimmediate4() success test - expected 0x4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg1\n");

    x = testarmasrreg1();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrreg1() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg2\n");

    x = testarmasrreg2();
    
    if (x != 0xC000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrreg2() success test - expected 0xC000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg3\n");

    x = testarmasrreg3();
    
    if (x != 0x2000000000000000ULL)
    {
    
       printf("  FAIL! testarmasrreg3() success test - expected 0x2000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg4\n");

    x = testarmasrreg4();
    
    if (x != 0xFFFFFFFFFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmasrreg4() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg5\n");

    x = testarmasrreg5();
    
    if (x != 0xC0000000ULL)
    {
    
       printf("  FAIL! testarmasrreg5() success test - expected 0xC0000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg6\n");

    x = testarmasrreg6();
    
    if (x != 0x20000000ULL)
    {
    
       printf("  FAIL! testarmasrreg6() success test - expected 0x20000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmasrreg7\n");

    x = testarmasrreg7();
    
    if (x != 0xFFFFFFFFULL)
    {
    
       printf("  FAIL! testarmasrreg7() success test - expected 0xFFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg1\n");

    x = testarmlsrreg1();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrreg1() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg2\n");

    x = testarmlsrreg2();
    
    if (x != 0x4000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrreg2() success test - expected 0x4000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg3\n");

    x = testarmlsrreg3();
    
    if (x != 0x2000000000000000ULL)
    {
    
       printf("  FAIL! testarmlsrreg3() success test - expected 0x2000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg4\n");

    x = testarmlsrreg4();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testarmlsrreg4() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg5\n");

    x = testarmlsrreg5();
    
    if (x != 0x40000000ULL)
    {
    
       printf("  FAIL! testarmlsrreg5() success test - expected 0x40000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg6\n");

    x = testarmlsrreg6();
    
    if (x != 0x20000000ULL)
    {
    
       printf("  FAIL! testarmlsrreg6() success test - expected 0x20000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlsrreg7\n");

    x = testarmlsrreg7();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testarmlsrreg7() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslreg1\n");

    x = testarmlslreg1();
    
    if (x != 0x0000000000000001ULL)
    {
    
       printf("  FAIL! testarmlslreg1() success test - expected 0x0000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslreg2\n");

    x = testarmlslreg2();
    
    if (x != 0x0000000000000002ULL)
    {
    
       printf("  FAIL! testarmlslreg2() success test - expected 0x0000000000000002, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslreg3\n");

    x = testarmlslreg3();
    
    if (x != 0x8000000000000000ULL)
    {
    
       printf("  FAIL! testarmlslreg3() success test - expected 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmlslreg4\n");

    x = testarmlslreg4();
    
    if (x != 0x4ULL)
    {
    
       printf("  FAIL! testarmlslreg4() success test - expected 0x4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testquerymovzork1\n");

    x = testquerymovzork1();
    
    if (x != 0x03040000ULL)
    {
    
       printf("  FAIL! testquerymovzork1() success test - expected 0x03040000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testquerymovzork2\n");

    x = testquerymovzork2();
    
    if (x != 0x03041212ULL)
    {
    
       printf("  FAIL! testquerymovzork2() success test - expected 0x03041212, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testquerymovnork1\n");

    x = testquerymovnork1();
    
    if (x != 0xFFFFFFFF0304FFFFULL)
    {
    
       printf("  FAIL! testquerymovnork1() success test - expected 0xFFFFFFFF0304FFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testquerymovnork2\n");

    x = testquerymovnork2();
    
    if (x != 0x03051212ULL)
    {
    
       printf("  FAIL! testquerymovnork2() success test - expected 0x03051212, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64a\n");

    x = testntoir64a();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testntoir64a() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64b\n");

    x = testntoir64b();
    
    if (x != (UINT64)-1)
    {
    
       printf("  FAIL! testntoir64b() success test - expected -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64c\n");

    x = testntoir64c();
    
    if (x != 0x1ULL)
    {
    
       printf("  FAIL! testntoir64c() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64d\n");

    x = testntoir64d();
    
    if (x != 0x20000ULL)
    {
    
       printf("  FAIL! testntoir64d() success test - expected 0x20000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64e\n");

    x = testntoir64e();
    
    if (x != 0x20001ULL)
    {
    
       printf("  FAIL! testntoir64e() success test - expected 0x20001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64f\n");

    x = testntoir64f();
    
    if (x != 0x300000000ULL)
    {
    
       printf("  FAIL! testntoir64f() success test - expected 0x300000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64g\n");

    x = testntoir64g();
    
    if (x != 0x300000001ULL)
    {
    
       printf("  FAIL! testntoir64g() success test - expected 0x300000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64h\n");

    x = testntoir64h();
    
    if (x != 0x300020000ULL)
    {
    
       printf("  FAIL! testntoir64h() success test - expected 0x300020000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64i\n");

    x = testntoir64i();
    
    if (x != 0x300020001ULL)
    {
    
       printf("  FAIL! testntoir64i() success test - expected 0x300020001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64j\n");

    x = testntoir64j();
    
    if (x != 0x4000000000000ULL)
    {
    
       printf("  FAIL! testntoir64j() success test - expected 0x4000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64k\n");

    x = testntoir64k();
    
    if (x != 0x4000000000001ULL)
    {
    
       printf("  FAIL! testntoir64k() success test - expected 0x4000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64l\n");

    x = testntoir64l();
    
    if (x != 0x4000000020000ULL)
    {
    
       printf("  FAIL! testntoir64l() success test - expected 0x4000000020000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64m\n");

    x = testntoir64m();
    
    if (x != 0x4000000020001ULL)
    {
    
       printf("  FAIL! testntoir64m() success test - expected 0x4000000020001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64n\n");

    x = testntoir64n();
    
    if (x != 0x4000300000000ULL)
    {
    
       printf("  FAIL! testntoir64n() success test - expected 0x4000300000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64o\n");

    x = testntoir64o();
    
    if (x != 0x4000300000001ULL)
    {
    
       printf("  FAIL! testntoir64o() success test - expected 0x4000300000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64p\n");

    x = testntoir64p();
    
    if (x != 0x4000300020000ULL)
    {
    
       printf("  FAIL! testntoir64p() success test - expected 0x4000300020000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64q\n");

    x = testntoir64q();
    
    if (x != 0x4000300020001ULL)
    {
    
       printf("  FAIL! testntoir64q() success test - expected 0x4000300020001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64r\n");

    x = testntoir64r();
    
    if (x != 0xFFFFFFFFFFFFFFF1ULL)
    {
    
       printf("  FAIL! testntoir64r() success test - expected 0xFFFFFFFFFFFFFFF1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64s\n");

    x = testntoir64s();
    
    if (x != 0xFFFFFFFFFFF2FFFFULL)
    {
    
       printf("  FAIL! testntoir64s() success test - expected 0xFFFFFFFFFFF2FFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64t\n");

    x = testntoir64t();
    
    if (x != 0xFFFFFFFFFFF2FFF1ULL)
    {
    
       printf("  FAIL! testntoir64t() success test - expected 0xFFFFFFFFFFF2FFF1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64u\n");

    x = testntoir64u();
    
    if (x != 0xFFFFFFF3FFFFFFFFULL)
    {
    
       printf("  FAIL! testntoir64u() success test - expected 0xFFFFFFF3FFFFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64v\n");

    x = testntoir64v();
    
    if (x != 0xFFFFFFF3FFFFFFF1ULL)
    {
    
       printf("  FAIL! testntoir64v() success test - expected 0xFFFFFFF3FFFFFFF1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64w\n");

    x = testntoir64w();
    
    if (x != 0xFFFFFFF3FFF2FFFFULL)
    {
    
       printf("  FAIL! testntoir64w() success test - expected 0xFFFFFFF3FFF2FFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64x\n");

    x = testntoir64x();
    
    if (x != 0xFFFFFFF3FFF2FFF1ULL)
    {
    
       printf("  FAIL! testntoir64x() success test - expected 0xFFFFFFF3FFF2FFF1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64y\n");

    x = testntoir64y();
    
    if (x != 0xFFFF000000000000ULL)
    {
    
       printf("  FAIL! testntoir64y() success test - expected 0xFFFF000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64z\n");

    x = testntoir64z();
    
    if (x != 0xFFFF000000001111ULL)
    {
    
       printf("  FAIL! testntoir64z() success test - expected 0xFFFF000000001111, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64aa\n");

    x = testntoir64aa();
    
    if (x != 0xFFFF111100000000ULL)
    {
    
       printf("  FAIL! testntoir64aa() success test - expected 0xFFFF111100000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64ab\n");

    x = testntoir64ab();
    
    if (x != 0xFFFF000011110000ULL)
    {
    
       printf("  FAIL! testntoir64ab() success test - expected 0xFFFF000011110000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testntoir64ac\n");

    x = testntoir64ac();
    
    if (x != 0x100000ULL)
    {
    
       printf("  FAIL! testntoir64ac() success test - expected 0x100000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64\n");

    x = testir64toir64();
    
    if (x != 0x9847ULL)
    {
    
       printf("  FAIL! testir64toir64() success test - expected 0x9847, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64a\n");

    y = ((UINT64)(&testpcplusntoir64a));
    x = testpcplusntoir64a();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64a() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64b\n");

    y = 0x4 + ((UINT64)(&testpcplusntoir64b));
    x = testpcplusntoir64b();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64b() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64c\n");

    y = 0x100 + ((UINT64)(&testpcplusntoir64c));
    x = testpcplusntoir64c();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64c() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64d\n");

    y = 0x10000 + ((UINT64)(&testpcplusntoir64d));
    x = testpcplusntoir64d();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64d() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64e\n");

    y = 0xFFFFF + ((UINT64)(&testpcplusntoir64e));
    x = testpcplusntoir64e();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64e() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64f\n");

    y = -0x100000 + ((UINT64)(&testpcplusntoir64f));
    x = testpcplusntoir64f();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64f() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64g\n");

    y = 0x100000 + ((UINT64)(&testpcplusntoir64g));
    x = testpcplusntoir64g();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64g() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64h\n");

    y = -0x100001 + ((UINT64)(&testpcplusntoir64h));
    x = testpcplusntoir64h();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpcplusntoir64h() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpctoir64a\n");

    y = ((UINT64)(&testpctoir64a));
    x = testpctoir64a();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testpctoir64a() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntopca\n");

    x = testpcplusntopca();
    
    if (x != 0x1579ULL)
    {
    
       printf("  FAIL! testpcplusntopca() success test - expected 0x1579, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntopcb\n");

    x = testpcplusntopcb();
    
    if (x != 0x1576ULL)
    {
    
       printf("  FAIL! testpcplusntopcb() success test - expected 0x1576, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntopcc\n");

    x = testpcplusntopcc();
    
    if (x != 0x8642ULL)
    {
    
       printf("  FAIL! testpcplusntopcc() success test - expected 0x1576, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64a\n");

    x = testir64plusntoir64a();
    
    if (x != 0x157BULL)
    {
    
       printf("  FAIL! testir64plusntoir64a() success test - expected 0x157B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64b\n");

    x = testir64plusntoir64b();
    
    if (x != 0x1577ULL)
    {
    
       printf("  FAIL! testir64plusntoir64b() success test - expected 0x1577, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64c\n");

    x = testir64plusntoir64c();
    
    if (x != 0x1575ULL)
    {
    
       printf("  FAIL! testir64plusntoir64c() success test - expected 0x1575, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64d\n");

    x = testir64plusntoir64d();
    
    if (x != 0x1FFFULL)
    {
    
       printf("  FAIL! testir64plusntoir64d() success test - expected 0x1FFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64e\n");

    x = testir64plusntoir64e();
    
    if (x != 0x1001ULL)
    {
    
       printf("  FAIL! testir64plusntoir64e() success test - expected 0x1001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64f\n");

    x = testir64plusntoir64f();
    
    if (x != -0xFFFULL)
    {
    
       printf("  FAIL! testir64plusntoir64f() success test - expected -0xFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64g\n");

    x = testir64plusntoir64g();
    
    if (x != 0x100001ULL)
    {
    
       printf("  FAIL! testir64plusntoir64g() success test - expected 0x100001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64h\n");

    x = testir64plusntoir64h();
    
    if (x != -0xFFFFFULL)
    {
    
       printf("  FAIL! testir64plusntoir64h() success test - expected -0xFFFFF, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusntoir64i\n");

    x = testir64plusntoir64i();
    
    if (x != 0x1353ULL)
    {
    
       printf("  FAIL! testir64plusntoir64i() success test - expected 0x1353, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrspplusntorspa\n");

    x = testrspplusntorspa();
    
    if (x != 0x1351ULL)
    {
    
       printf("  FAIL! testrspplusntorspa() success test - expected 0x1351, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toir64a\n");

    x = testbracketir64toir64a();
    
    if (x != 0x1349ULL)
    {
    
       printf("  FAIL! testbracketir64toir64a() success test - expected 0x1351, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toir64b\n");

    x = testbracketir64toir64b();
    
    if (x != 0x1347ULL)
    {
    
       printf("  FAIL! testbracketir64toir64b() success test - expected 0x1347, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrsptoir64a\n");

    x = testrsptoir64a();
    
    if (x != 0x1348ULL)
    {
    
       printf("  FAIL! testrsptoir64a() success test - expected 0x1348, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64torspa\n");

    x = testir64torspa();
    
    if (x != 0x1349ULL)
    {
    
       printf("  FAIL! testir64torspa() success test - expected 0x1349, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrspplusntoir64a\n");

    x = testrspplusntoir64a();
    
    if (x != 0x1030ULL)
    {
    
       printf("  FAIL! testrspplusntoir64a() success test - expected 0x1030, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrspplusntoir64b\n");

    x = testrspplusntoir64b();
    
    if (x != -0x1030LL)
    {
    
       printf("  FAIL! testrspplusntoir64b() success test - expected -0x1030, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrspplusntoir64c\n");

    x = testrspplusntoir64c();
    
    if (x != 0x40ULL)
    {
    
       printf("  FAIL! testrspplusntoir64c() success test - expected 0x40, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrspplusntoir64d\n");

    x = testrspplusntoir64d();
    
    if (x != -0x40LL)
    {
    
       printf("  FAIL! testrspplusntoir64d() success test - expected -0x40, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
       return(1);

    }

    printf("  testing testbracketpcplusntoir64a\n");

    x = testbracketpcplusntoir64a();
    y = 0x1122131477668640ULL;

    if (x != y)
    {
       printf("  FAIL! testbracketpcplusntoir64a() success test - expected 0x1122131477668640, testing against 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
       return(1);

    }

    printf("  testing testbracketpcplusntoir64b\n");

    x = testbracketpcplusntoir64b();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testbracketpcplusntoir64b() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
       return(1);

    }

    printf("  testing testbracketpcplusntoir64c\n");

    x = testbracketpcplusntoir64c();
    
    if (x != 0x1122131477668641ULL)
    {
    
       printf("  FAIL! testbracketpcplusntoir64c() success test - expected 0x1122131477668641, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testpcplusntoir64a\n");

    y = ptestconstant1;
    x = testotoir64a();
    
    if (x !=  y)
    {
    
       printf("  FAIL! testotoir64a() success test - expected address of 0x%08x%08x, got 0x%08x%08x\n",
         ((UINT32*)(&y))[1],
         ((UINT32*)(&y))[0],
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketotoir64a\n");

    x = testbracketotoir64a();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testbracketotoir64a() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64tobracketir64a\n");

    x = testir64tobracketir64a();
    
    if (x != 0x1397ULL)
    {
    
       printf("  FAIL! testir64tobracketir64a() success test - expected 0x1397, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusir64toir64a\n");

    x = testbracketir64plusir64toir64a();
    
    if (x != 0x7318ULL)
    {
    
       printf("  FAIL! testbracketir64plusir64toir64a() success test - expected 0x7318, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64tobracketir64plusir64a\n");

    x = testir64tobracketir64plusir64a();
    
    if (x != 0x7319ULL)
    {
    
       printf("  FAIL! testir64tobracketir64plusir64a() success test - expected 0x7318, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64a\n");

    x = testbracketir64plusntoir64a();
    
    if (x != 0x1122131477668640ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64a() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64b\n");

    x = testbracketir64plusntoir64b();
    
    if (x != 0x9988776652535455ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64b() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64c\n");

    x = testbracketir64plusntoir64c();
    
    if (x != 0x8182838485868788ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64c() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64d\n");

    x = testbracketir64plusntoir64d();
    
    if (x != 0x2122334455667780ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64d() success test - expected 0x1122334455667780, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64e\n");

    x = testbracketir64plusntoir64e();
    
    if (x != 0x2122334455667781ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64e() success test - expected 0x1122334455667781, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64f\n");

    x = testbracketir64plusntoir64f();
    
    if (x != 0x3122334455667780ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64f() success test - expected 0x3122334455667780, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64g\n");

    x = testbracketir64plusntoir64g();
    
    if (x != 0x3122334455667781ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64g() success test - expected 0x3122334455667781, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoir64h\n");

    x = testbracketir64plusntoir64h();
    
    if (x != 0x1122334455667780ULL)
    {
    
       printf("  FAIL! testbracketir64plusntoir64h() success test - expected 0x1122334455667780, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcfinva\n");

    x = testarmcfinva();
    
    if (x != 0x8374ULL)
    {
    
       printf("  FAIL! testarmcfinva() success test - expected 0x8374, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcfinvb\n");

    x = testarmcfinvb();
    
    if (x != 0x1287ULL)
    {
    
       printf("  FAIL! testarmcfinvb() success test - expected 0x1287, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toir64plusna\n");

    x = testbracketir64toir64plusna();
    
    if (x != 0x1248ULL)
    {
    
       printf("  FAIL! testbracketir64toir64plusna() success test - expected 0x1238, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toir64plusnb\n");

    x = testbracketir64toir64plusnb();
    
    if (x != 0x7449ULL)
    {
    
       printf("  FAIL! testbracketir64toir64plusnb() success test - expected 0x7439, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketrspplusntoir64a\n");

    x = testbracketrspplusntoir64a();
    
    if (x != 0x1238ULL)
    {
    
       printf("  FAIL! testbracketrspplusntoir64a() success test - expected 0x1238, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketrspplusntoir64b\n");

    x = testbracketrspplusntoir64b();
    
    if (x != 0x7439ULL)
    {
    
       printf("  FAIL! testbracketrspplusntoir64b() success test - expected 0x7439, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64tobracketrspplusna\n");

    x = testir64tobracketrspplusna();
    
    if (x != 0x1258ULL)
    {
    
       printf("  FAIL! testir64tobracketrspplusna() success test - expected 0x1258, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64tobracketrspplusnb\n");

    x = testir64tobracketrspplusnb();
    
    if (x != 0x7459ULL)
    {
    
       printf("  FAIL! testir64tobracketrspplusnb() success test - expected 0x7459, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64opa\n");

    x = testir64ir64toir64opa();
    
    if (x != 0xAB95ULL)
    {
    
       printf("  FAIL! testir64ir64toir64opa() success test - expected 0xAB95, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64opb\n");

    x = testir64ir64toir64opb();
    
    if (x != 2ULL)
    {
    
       printf("  FAIL! testir64ir64toir64opb() success test - expected 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfa\n");

    x = testir64ir64toir64idpfa();
    
    if (x != 0xF110ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfa() success test - expected 0xF110, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfb\n");

    x = testir64ir64toir64idpfb();
    
    if (x != 0xF111ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfb() success test - expected 0xF111, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfc\n");

    x = testir64ir64toir64idpfc();
    
    if (x != 0xEF0DULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfc() success test - expected 0xEF0D, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfd\n");

    x = testir64ir64toir64idpfd();
    
    if (x != 0xEF0EULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfd() success test - expected 0xEF0E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfe\n");

    x = testir64ir64toir64idpfe();
    
    if (x != 0x0001ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfe() success test - expected 0x0001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpff\n");

    x = testir64ir64toir64idpff();
    
    if (x != 0xF10FULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpff() success test - expected 0xF10F, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfg\n");

    x = testir64ir64toir64idpfg();
    
    if (x != 0xF10EULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfg() success test - expected 0xF10E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfh\n");

    x = testir64ir64toir64idpfh();
    
    if (x != 0xFFFFFFFFFFFFFFFEULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfh() success test - expected 0xFFFFFFFFFFFFFFFE, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfi\n");

    x = testir64ir64toir64idpfi();
    
    if (x != 0xFFFFFFFFFFFF0EF0ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfi() success test - expected 0xFFFFFFFFFFFF0EF0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfj\n");

    x = testir64ir64toir64idpfj();
    
    if (x != 0xFFFFFFFFFFFF0EF1ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfj() success test - expected 0xFFFFFFFFFFFF0EF1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfk\n");

    x = testir64ir64toir64idpfk();
    
    if (x != 0xF110ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfk() success test - expected 0xF110, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfl\n");

    x = testir64ir64toir64idpfl();
    
    if (x != 0xF110ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfl() success test - expected 0xF110, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfm\n");

    x = testir64ir64toir64idpfm();
    
    if (x != 0xEF0EULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfm() success test - expected 0xEF0E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfn\n");

    x = testir64ir64toir64idpfn();
    
    if (x != 0xEF0EULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfn() success test - expected 0xEF0E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfo\n");

    x = testir64ir64toir64idpfo();
    
    if (x != 0xF00EULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfo() success test - expected 0xF00E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfp\n");

    x = testir64ir64toir64idpfp();
    
    if (x != -0x5ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfp() success test - expected -0x5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfq\n");

    x = testir64ir64toir64idpfq();
    
    if (x != 0x5ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfq() success test - expected 0x5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfr\n");

    x = testir64ir64toir64idpfr();
    
    if (x != 0x0ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfr() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfs\n");

    x = testir64ir64toir64idpfs();
    
    if (x != 0x5ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfs() success test - expected 0x5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpft\n");

    x = testir64ir64toir64idpft();
    
    if (x != -0x2DLL)
    {
    
       printf("  FAIL! testir64ir64toir64idpft() success test - expected -0x2D, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfu\n");

    x = testir64ir64toir64idpfu();
    
    if (x != 0x2DULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfu() success test - expected 0x2D, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfv\n");

    x = testir64ir64toir64idpfv();
    
    if (x != 0xFF00CF00DF00EF00ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfv() success test - expected 0xFF00CF00DF00EF00, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfw\n");

    x = testir64ir64toir64idpfw();
    
    if (x != 0x0F00CF00DF00EF00ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfw() success test - expected 0x0F00CF00DF00EF00, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfx\n");

    x = testir64ir64toir64idpfx();
    
    if (x != 0x00CF00DF00EF00F0ULL)
    {
    
       printf("  FAIL! testir64ir64toir64idpfx() success test - expected 0x00CF00DF00EF00F0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idpfy\n");

    x = testir64ir64toir64idpfy();
    y = 0xFF00CF00DF00EF00ULL;
   
    if (x != y)
    {
    
        printf("  FAIL! testir64ir64toir64idpfy() success test - expected 0xFF00CF00DF00EF00, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfa\n");

    x = testir64ir64toir64idcfa();
   
    if (x != 0x9865)
    {
    
        printf("  FAIL! testir64ir64toir64idcfa() success test - expected 0x9865, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfb\n");

    x = testir64ir64toir64idcfb();
   
    if (x != 0x9864)
    {
    
        printf("  FAIL! testir64ir64toir64idcfb() success test - expected 0x9864, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfc\n");

    x = testir64ir64toir64idcfc();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfc() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfd\n");

    x = testir64ir64toir64idcfd();
   
    if (x != 0x9867)
    {
    
        printf("  FAIL! testir64ir64toir64idcfd() success test - expected 0x9867, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfe\n");

    x = testir64ir64toir64idcfe();
   
    if (x != 0x9868)
    {
    
        printf("  FAIL! testir64ir64toir64idcfe() success test - expected 0x9868, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcff\n");

    x = testir64ir64toir64idcff();
   
    if (x != 0x9869)
    {
    
        printf("  FAIL! testir64ir64toir64idcff() success test - expected 0x9869, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfg\n");

    x = testir64ir64toir64idcfg();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testir64ir64toir64idcfg() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfh\n");

    x = testir64ir64toir64idcfh();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfh() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfi\n");

    x = testir64ir64toir64idcfi();
   
    if (x != 0x9870)
    {
    
        printf("  FAIL! testir64ir64toir64idcfi() success test - expected 0x9870, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfj\n");

    x = testir64ir64toir64idcfj();
   
    if (x != 0x9871)
    {
    
        printf("  FAIL! testir64ir64toir64idcfj() success test - expected 0x9871, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfk\n");

    x = testir64ir64toir64idcfk();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfk() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfl\n");

    x = testir64ir64toir64idcfl();
   
    if (x != 0x2)
    {
    
        printf("  FAIL! testir64ir64toir64idcfl() success test - expected 0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfm\n");

    x = testir64ir64toir64idcfm();
   
    if (x != 0xC)
    {
    
        printf("  FAIL! testir64ir64toir64idcfm() success test - expected 0xC, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfn\n");

    x = testir64ir64toir64idcfn();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testir64ir64toir64idcfn() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfo\n");

    x = testir64ir64toir64idcfo();
   
    if (x != 0x2)
    {
    
        printf("  FAIL! testir64ir64toir64idcfo() success test - expected 0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfp\n");

    x = testir64ir64toir64idcfp();
   
    if (x != 0x9882)
    {
    
        printf("  FAIL! testir64ir64toir64idcfp() success test - expected 0x9882, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfq\n");

    x = testir64ir64toir64idcfq();
   
    if (x != 0x9883)
    {
    
        printf("  FAIL! testir64ir64toir64idcfq() success test - expected 0x9883, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfr\n");

    x = testir64ir64toir64idcfr();
   
    if (x != 0x9884)
    {
    
        printf("  FAIL! testir64ir64toir64idcfr() success test - expected 0x9884, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfs\n");

    x = testir64ir64toir64idcfs();
   
    if (x != 0x9885)
    {
    
        printf("  FAIL! testir64ir64toir64idcfs() success test - expected 0x9885, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcft\n");

    x = testir64ir64toir64idcft();
   
    if (x != 0x5)
    {
    
        printf("  FAIL! testir64ir64toir64idcft() success test - expected 0x5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    printf("  testing testir64ir64toir64idcfu\n");

    x = testir64ir64toir64idcfu();
   
    if (x != -0x5)
    {
    
        printf("  FAIL! testir64ir64toir64idcfu() success test - expected -0x5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfv\n");

    x = testir64ir64toir64idcfv();
   
    if (x != 0xF812345678112334)
    {
    
        printf("  FAIL! testir64ir64toir64idcfv() success test - expected 0xF812345678112334, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfw\n");

    x = testir64ir64toir64idcfw();
   
    if (x != 0x9886)
    {
    
        printf("  FAIL! testir64ir64toir64idcfw() success test - expected 0x9886, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfx\n");

    x = testir64ir64toir64idcfx();
   
    if (x != 0x9887)
    {
    
        printf("  FAIL! testir64ir64toir64idcfx() success test - expected 0x9886, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfy\n");

    x = testir64ir64toir64idcfy();
   
    if (x != 0x0812345678112334)
    {
    
        printf("  FAIL! testir64ir64toir64idcfy() success test - expected 0x0812345678112334, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfz\n");

    x = testir64ir64toir64idcfz();
   
    if (x != 0x9888)
    {
    
        printf("  FAIL! testir64ir64toir64idcfz() success test - expected 0x9888, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaa\n");

    x = testir64ir64toir64idcfaa();
   
    if (x != 0x9889)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaa() success test - expected 0x9889, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfab\n");

    x = testir64ir64toir64idcfab();
   
    if (x != 0x1234567811233440)
    {
    
        printf("  FAIL! testir64ir64toir64idcfab() success test - expected 0x1234567811233440, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfac\n");

    x = testir64ir64toir64idcfac();
   
    if (x != 0x988A)
    {
    
        printf("  FAIL! testir64ir64toir64idcfac() success test - expected 0x988A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfad\n");

    x = testir64ir64toir64idcfad();
   
    if (x != 0x988B)
    {
    
        printf("  FAIL! testir64ir64toir64idcfad() success test - expected 0x988B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfae\n");

    x = testir64ir64toir64idcfae();
   
    if (x != 0x4812345678112334)
    {
    
        printf("  FAIL! testir64ir64toir64idcfae() success test - expected 0x4812345678112334, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaf\n");

    x = testir64ir64toir64idcfaf();
   
    if (x != 0x988C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaf() success test - expected 0x988C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfag\n");

    x = testir64ir64toir64idcfag();
   
    if (x != 0x988D)
    {
    
        printf("  FAIL! testir64ir64toir64idcfag() success test - expected 0x988D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfah\n");

    x = testir64ir64toir64idcfah();
   
    if (x != 0x3C00)
    {
    
        printf("  FAIL! testir64ir64toir64idcfah() success test - expected 0x3C00, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfai\n");

    x = testir64ir64toir64idcfai();
   
    if (x != 0x988E)
    {
    
        printf("  FAIL! testir64ir64toir64idcfai() success test - expected 0x988E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaj\n");

    x = testir64ir64toir64idcfaj();
   
    if (x != 0x988F)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaj() success test - expected 0x988F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfak\n");

    x = testir64ir64toir64idcfak();
   
    if (x != 0xFF3C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfak() success test - expected 0xFF3C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfal\n");

    x = testir64ir64toir64idcfal();
   
    if (x != 0x9890)
    {
    
        printf("  FAIL! testir64ir64toir64idcfal() success test - expected 0x9890, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfam\n");

    x = testir64ir64toir64idcfam();
   
    if (x != 0x9891)
    {
    
        printf("  FAIL! testir64ir64toir64idcfam() success test - expected 0x9891, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfan\n");

    x = testir64ir64toir64idcfan();
   
    if (x != 0xC33C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfan() success test - expected 0x9891, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfao\n");

    x = testir64ir64toir64idcfao();
   
    if (x != 0x9892)
    {
    
        printf("  FAIL! testir64ir64toir64idcfao() success test - expected 0x9891, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfap\n");

    x = testir64ir64toir64idcfap();
   
    if (x != 0x9893)
    {
    
        printf("  FAIL! testir64ir64toir64idcfap() success test - expected 0x9893, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaq\n");

    x = testir64ir64toir64idcfaq();
   
    if (x != 0xFFFFFFFFFFFFC3FF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaq() success test - expected 0x003C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfar\n");

    x = testir64ir64toir64idcfar();
   
    if (x != 0x9894)
    {
    
        printf("  FAIL! testir64ir64toir64idcfar() success test - expected 0x9894, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfas\n");

    x = testir64ir64toir64idcfas();
   
    if (x != 0x9895)
    {
    
        printf("  FAIL! testir64ir64toir64idcfas() success test - expected 0x9895, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfat\n");

    x = testir64ir64toir64idcfat();
   
    if (x != 0xFFFFFFFFFFFF00C3)
    {
    
        printf("  FAIL! testir64ir64toir64idcfat() success test - expected 0xFFFFFFFFFFFF00C3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfau\n");

    x = testir64ir64toir64idcfau();
   
    if (x != 0x9896)
    {
    
        printf("  FAIL! testir64ir64toir64idcfau() success test - expected 0x9896, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfav\n");

    x = testir64ir64toir64idcfav();
   
    if (x != 0x9897)
    {
    
        printf("  FAIL! testir64ir64toir64idcfav() success test - expected 0x9897, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaw\n");

    x = testir64ir64toir64idcfaw();
   
    if (x != 0xFFFFFFFFFFFF00C3)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaw() success test - expected 0xFFFFFFFFFFFF00C3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfax\n");

    x = testir64ir64toir64idcfax();
   
    if (x != 0xFF00)
    {
    
        printf("  FAIL! testir64ir64toir64idcfax() success test - expected 0xFF00, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfay\n");

    x = testir64ir64toir64idcfay();
   
    if (x != 0xFFFFFFFFFFFFC3C3)
    {
    
        printf("  FAIL! testir64ir64toir64idcfay() success test - expected 0xFFFFFFFFFFFFC3C3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfaz\n");

    x = testir64ir64toir64idcfaz();
   
    if (x != 0xFFFFFFFFFFFFCC33)
    {
    
        printf("  FAIL! testir64ir64toir64idcfaz() success test - expected 0xFFFFFFFFFFFFCC33, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfba\n");

    x = testir64ir64toir64idcfba();
   
    if (x != 0xFFFFFFFFFFFF3CC3)
    {
    
        printf("  FAIL! testir64ir64toir64idcfba() success test - expected 0xFFFFFFFFFFFF3CC3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbb\n");

    x = testir64ir64toir64idcfbb();
   
    if (x != 0x23)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbb() success test - expected 0x32, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbc\n");

    x = testir64ir64toir64idcfbc();
   
    if (x != 0x9898)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbc() success test - expected 0x9898, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbd\n");

    x = testir64ir64toir64idcfbd();
   
    if (x != 0x9899)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbd() success test - expected 0x9899, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbe\n");

    x = testir64ir64toir64idcfbe();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbe() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbf\n");

    x = testir64ir64toir64idcfbf();
   
    if (x != 0x989A)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbf() success test - expected 0x989A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbg\n");

    x = testir64ir64toir64idcfbg();
   
    if (x != 0x989B)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbg() success test - expected 0x989B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbh\n");

    x = testir64ir64toir64idcfbh();
   
    if (x != 0x333333333333332C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbh() success test - expected 0x333333333333332C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbi\n");

    x = testir64ir64toir64idcfbi();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbi() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbj\n");

    x = testir64ir64toir64idcfbj();
   
    if (x != 0x989C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbj() success test - expected 0x989C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbk\n");

    x = testir64ir64toir64idcfbk();
   
    if (x != 0x989D)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbk() success test - expected 0x989D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbl\n");

    x = testir64ir64toir64idcfbl();
   
    if (x != -0x7)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbl() success test - expected -0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbm\n");

    x = testir64ir64toir64idcfbm();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbm() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbn\n");

    x = testir64ir64toir64idcfbn();
   
    if (x != 0x7FFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbn() success test - expected 0x7FFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbo\n");

    x = testir64ir64toir64idcfbo();
   
    if (x != 0x3C)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbo() success test - expected 0x3C00, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idcfbp\n");

    x = testir64ir64toir64idcfbp();
   
    if (x != 0xFFFFFFFFFFFF3CFF)
    {
    
        printf("  FAIL! testir64ir64toir64idcfbp() success test - expected 0x3C00, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfa\n");

    x = testir64ntoir64idpfa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testir64ntoir64idpfa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfb\n");

    x = testir64ntoir64idpfb();
   
    if (x != 0x185)
    {
    
        printf("  FAIL! testir64ntoir64idpfb() success test - expected 0x185, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfc\n");

    x = testir64ntoir64idpfc();
   
    if (x != 0x1181)
    {
    
        printf("  FAIL! testir64ntoir64idpfc() success test - expected 0x1181, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfd\n");

    x = testir64ntoir64idpfd();
   
    if (x != 0x1182)
    {
    
        printf("  FAIL! testir64ntoir64idpfd() success test - expected 0x1182, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfe\n");

    x = testir64ntoir64idpfe();
   
    if (x != 0xFFF182)
    {
    
        printf("  FAIL! testir64ntoir64idpfe() success test - expected 0xFFF182, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpff\n");

    x = testir64ntoir64idpff();
   
    if (x != 0xFFF183)
    {
    
        printf("  FAIL! testir64ntoir64idpff() success test - expected 0xFFF183, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfg\n");

    x = testir64ntoir64idpfg();
   
    if (x != 0x17F)
    {
    
        printf("  FAIL! testir64ntoir64idpfg() success test - expected 0x17F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatea\n");

    x = testarmandimmediatea();
    
    if (x != 0x5555555555555555)
    {
    
       printf("  FAIL! testarmandimmediatea() success test - expected 0x5555555555555555, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediateb\n");

    x = testarmandimmediateb();
    
    if (x != 0xAAAAAAAAAAAAAAAA)
    {
    
       printf("  FAIL! testarmandimmediateb() success test - expected 0xAAAAAAAAAAAAAAAA, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatec\n");

    x = testarmandimmediatec();
    
    if (x != 0x1111111111111111)
    {
    
       printf("  FAIL! testarmandimmediatec() success test - expected 0x1111111111111111, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediated\n");

    x = testarmandimmediated();
    
    if (x != 0x8888888888888888)
    {
    
       printf("  FAIL! testarmandimmediated() success test - expected 0x8888888888888888, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatee\n");

    x = testarmandimmediatee();
    
    if (x != 0x3333333333333333)
    {
    
       printf("  FAIL! testarmandimmediatee() success test - expected 0x3333333333333333, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatef\n");

    x = testarmandimmediatef();
    
    if (x != 0x7777777777777777)
    {
    
       printf("  FAIL! testarmandimmediatef() success test - expected 0x7777777777777777, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediateg\n");

    x = testarmandimmediateg();
    
    if (x != 0x0101010101010101)
    {
    
       printf("  FAIL! testarmandimmediateg() success test - expected 0x0101010101010101, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediateh\n");

    x = testarmandimmediateh();
    
    if (x != 0x8080808080808080)
    {
    
       printf("  FAIL! testarmandimmediateh() success test - expected 0x8080808080808080, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatei\n");

    x = testarmandimmediatei();
    
    if (x != 0x0001000100010001)
    {
    
       printf("  FAIL! testarmandimmediatei() success test - expected 0x0001000100010001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatej\n");

    x = testarmandimmediatej();
    
    if (x != 0x0000000100000001)
    {
    
       printf("  FAIL! testarmandimmediatej() success test - expected 0x0000000100000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatek\n");

    x = testarmandimmediatek();
    
    if (x != 0x0000000000000001)
    {
    
       printf("  FAIL! testarmandimmediatek() success test - expected 0x0000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmorimmediatea\n");

    x = testarmorimmediatea();
    
    if (x != 0x0000000000000001)
    {
    
       printf("  FAIL! testarmorimmediatea() success test - expected 0x0000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmorimmediateb\n");

    x = testarmorimmediateb();
    
    if (x != 0x8000000000000001)
    {
    
       printf("  FAIL! testarmorimmediateb() success test - expected 0x8000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandimmediatel\n");

    x = testarmandimmediatel();
    
    if (x != 0x0000000000000001)
    {
    
       printf("  FAIL! testarmandimmediatel() success test - expected 0x0000000000000001, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmorimmediatec\n");

    x = testarmorimmediatec();
    
    if (x != 0x0000000000000007)
    {
    
       printf("  FAIL! testarmorimmediatec() success test - expected 0x0000000000000007, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmeorimmediatea\n");

    x = testarmeorimmediatea();
    
    if (x != 0x0000000000000006)
    {
    
       printf("  FAIL! testarmeorimmediatea() success test - expected 0x0000000000000006, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfh\n");

    x = testir64ntoir64idpfh();
    
    if (x != 0xC000C000C000C000)
    {
    
       printf("  FAIL! testir64ntoir64idpfh() success test - expected 0xC000C000C000C000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idpfi\n");

    x = testir64ntoir64idpfi();
    
    if (x != 0xC000000000000000)
    {
    
       printf("  FAIL! testir64ntoir64idpfi() success test - expected 0xC000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfa\n");

    x = testir64ntoir64idcfa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testir64ntoir64idcfa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfa2\n");

    x = testir64ntoir64idcfa2();
   
    if (x != 0x8130)
    {
    
        printf("  FAIL! testir64ntoir64idcfa2() success test - expected 0x8130, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfa3\n");

    x = testir64ntoir64idcfa3();
   
    if (x != 0x8131)
    {
    
        printf("  FAIL! testir64ntoir64idcfa3() success test - expected 0x8131, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfb\n");

    x = testir64ntoir64idcfb();
   
    if (x != 0x185)
    {
    
        printf("  FAIL! testir64ntoir64idcfb() success test - expected 0x185, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfb2\n");

    x = testir64ntoir64idcfb2();
   
    if (x != 0x8132)
    {
    
        printf("  FAIL! testir64ntoir64idcfb2() success test - expected 0x8132, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfb3\n");

    x = testir64ntoir64idcfb3();
   
    if (x != 0x8142)
    {
    
        printf("  FAIL! testir64ntoir64idcfb3() success test - expected 0x8142, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfc\n");

    x = testir64ntoir64idcfc();
   
    if (x != 0x1181)
    {
    
        printf("  FAIL! testir64ntoir64idcfc() success test - expected 0x1181, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfc2\n");

    x = testir64ntoir64idcfc2();
   
    if (x != 0x8133)
    {
    
        printf("  FAIL! testir64ntoir64idcfc2() success test - expected 0x8133, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfc3\n");

    x = testir64ntoir64idcfc3();
   
    if (x != 0x8143)
    {
    
        printf("  FAIL! testir64ntoir64idcfc3() success test - expected 0x8143, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfd\n");

    x = testir64ntoir64idcfd();
   
    if (x != 0x1182)
    {
    
        printf("  FAIL! testir64ntoir64idcfd() success test - expected 0x1182, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfd2\n");

    x = testir64ntoir64idcfd2();
   
    if (x != 0x8134)
    {
    
        printf("  FAIL! testir64ntoir64idcfd2() success test - expected 0x8134, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfd3\n");

    x = testir64ntoir64idcfd3();
   
    if (x != 0x8144)
    {
    
        printf("  FAIL! testir64ntoir64idcfd3() success test - expected 0x8144, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfe\n");

    x = testir64ntoir64idcfe();
   
    if (x != 0xFFF182)
    {
    
        printf("  FAIL! testir64ntoir64idcfe() success test - expected 0xFFF182, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfe2\n");

    x = testir64ntoir64idcfe2();
   
    if (x != 0x8135)
    {
    
        printf("  FAIL! testir64ntoir64idcfe2() success test - expected 0x8135, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfe3\n");

    x = testir64ntoir64idcfe3();
   
    if (x != 0x8145)
    {
    
        printf("  FAIL! testir64ntoir64idcfe3() success test - expected 0x8145, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcff\n");

    x = testir64ntoir64idcff();
   
    if (x != 0xFFF183)
    {
    
        printf("  FAIL! testir64ntoir64idcff() success test - expected 0xFFF183, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcff2\n");

    x = testir64ntoir64idcff2();
   
    if (x != 0x8136)
    {
    
        printf("  FAIL! testir64ntoir64idcff2() success test - expected 0x8136, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcff3\n");

    x = testir64ntoir64idcff3();
   
    if (x != 0x8146)
    {
    
        printf("  FAIL! testir64ntoir64idcff3() success test - expected 0x8146, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfg\n");

    x = testir64ntoir64idcfg();
   
    if (x != 0x17F)
    {
    
        printf("  FAIL! testir64ntoir64idcfg() success test - expected 0x17F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfg2\n");

    x = testir64ntoir64idcfg2();
   
    if (x != 0x8137)
    {
    
        printf("  FAIL! testir64ntoir64idcfg2() success test - expected 0x8137, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idcfg3\n");

    x = testir64ntoir64idcfg3();
   
    if (x != 0x8147)
    {
    
        printf("  FAIL! testir64ntoir64idcfg3() success test - expected 0x8147, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2a\n");

    x = testmatoscratchreg2a();
   
    if (x != 0x1239)
    {
    
        printf("  FAIL! testmatoscratchreg2a() success test - expected 0x1239, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2b\n");

    x = testmatoscratchreg2b();
   
    if (x != 0x1249)
    {
    
        printf("  FAIL! testmatoscratchreg2b() success test - expected 0x1249, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2c\n");

    x = testmatoscratchreg2c();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmatoscratchreg2c() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2d\n");

    x = testmatoscratchreg2d();
   
    if (x != 0x9988776652535455)
    {
    
        printf("  FAIL! testmatoscratchreg2d() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2e\n");

    x = testmatoscratchreg2e();
   
    if (x != 0x1259)
    {
    
        printf("  FAIL! testmatoscratchreg2e() success test - expected 0x1259, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2f\n");

    x = testmatoscratchreg2f();
   
    if (x != 0x1269)
    {
    
        printf("  FAIL! testmatoscratchreg2f() success test - expected 0x1269, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2g\n");

    x = testmatoscratchreg2g();
   
    if (x != 0x9234183491831930)
    {
    
        printf("  FAIL! testmatoscratchreg2g() success test - expected 0x9234183491831930, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1a\n");

    x = testmbtoscratchreg1a();
   
    if (x != 0x1239)
    {
    
        printf("  FAIL! testmbtoscratchreg1a() success test - expected 0x1239, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1b\n");

    x = testmbtoscratchreg1b();
   
    if (x != 0x1249)
    {
    
        printf("  FAIL! testmbtoscratchreg1b() success test - expected 0x1249, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1c\n");

    x = testmbtoscratchreg1c();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmbtoscratchreg1c() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1d\n");

    x = testmbtoscratchreg1d();
   
    if (x != 0x9988776652535455)
    {
    
        printf("  FAIL! testmbtoscratchreg1d() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1e\n");

    x = testmbtoscratchreg1e();
   
    if (x != 0x1259)
    {
    
        printf("  FAIL! testmbtoscratchreg1e() success test - expected 0x1259, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1f\n");

    x = testmbtoscratchreg1f();
   
    if (x != 0x1269)
    {
    
        printf("  FAIL! testmbtoscratchreg1f() success test - expected 0x1269, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1g\n");

    x = testmbtoscratchreg1g();
   
    if (x != 0x9234183491831930)
    {
    
        printf("  FAIL! testmbtoscratchreg1g() success test - expected 0x9234183491831930, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2tomdesta\n");

    x = testscratchreg2tomdesta();
   
    if (x != 0x1982)
    {
    
        printf("  FAIL! testscratchreg2tomdesta() success test - expected 0x1982, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2tomdestb\n");

    x = testscratchreg2tomdestb();
   
    if (x != 0x1992)
    {
    
        printf("  FAIL! testscratchreg2tomdestb() success test - expected 0x1992, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2tomdestc\n");

    x = testscratchreg2tomdestc();
   
    if (x != 0x19A2)
    {
    
        printf("  FAIL! testscratchreg2tomdestc() success test - expected 0x19A2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpfa\n");

    x = testnir64toir64idpfa();
   
    if (x != 0x2356)
    {
    
        printf("  FAIL! testnir64toir64idpfa() success test - expected 0x2356, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpfb\n");

    x = testnir64toir64idpfb();
   
    if (x != 0x87652356)
    {
    
        printf("  FAIL! testnir64toir64idpfb() success test - expected 0x87652356, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpfc\n");

    x = testnir64toir64idpfc();
   
    if (x != 0x113)
    {
    
        printf("  FAIL! testnir64toir64idpfc() success test - expected 0x113, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpfd\n");

    x = testnir64toir64idpfd();
   
    if (x != 0x87650113)
    {
    
        printf("  FAIL! testnir64toir64idpfd() success test - expected 0x87650113, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpfe\n");

    x = testnir64toir64idpfe();
   
    if (x != 0x1298)
    {
    
        printf("  FAIL! testnir64toir64idpfe() success test - expected 0x1298, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idpff\n");

    x = testnir64toir64idpff();
   
    if (x != 0x1297)
    {
    
        printf("  FAIL! testnir64toir64idpff() success test - expected 0x1297, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64ida\n");

    x = testir64ir64toir64ida();
   
    if (x != 0x3337)
    {
    
        printf("  FAIL! testir64ir64toir64ida() success test - expected 0x3337, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idb\n");

    x = testir64ir64toir64idb();
   
    if (x != 0x9283)
    {
    
        printf("  FAIL! testir64ir64toir64idb() success test - expected 0x9283, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ir64toir64idc\n");

    x = testir64ir64toir64idc();
   
    if (x != 0x9284)
    {
    
        printf("  FAIL! testir64ir64toir64idc() success test - expected 0x9284, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64ida\n");

    x = testir64ntoir64ida();
   
    if (x != 0x2324)
    {
    
        printf("  FAIL! testir64ntoir64ida() success test - expected 0x2324, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idb\n");

    x = testir64ntoir64idb();
   
    if (x != 0x9271)
    {
    
        printf("  FAIL! testir64ntoir64idb() success test - expected 0x9271, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64ntoir64idc\n");

    x = testir64ntoir64idc();
   
    if (x != 0x9272)
    {
    
        printf("  FAIL! testir64ntoir64idc() success test - expected 0x9272, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64ida\n");

    x = testnir64toir64ida();
   
    if (x != 0x2325)
    {
    
        printf("  FAIL! testnir64toir64ida() success test - expected 0x2325, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idb\n");

    x = testnir64toir64idb();
   
    if (x != 0x9273)
    {
    
        printf("  FAIL! testnir64toir64idb() success test - expected 0x9271, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnir64toir64idc\n");

    x = testnir64toir64idc();
   
    if (x != 0x9274)
    {
    
        printf("  FAIL! testnir64toir64idc() success test - expected 0x9274, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaa\n");

    x = testaddcommaa();
   
    if (x != 0x3008)
    {
    
        printf("  FAIL! testaddcommaa() success test - expected 0x3008, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommab\n");

    x = testaddcommab();
   
    if (x != 0x3009)
    {
    
        printf("  FAIL! testaddcommab() success test - expected 0x3009, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommac\n");

    x = testaddcommac();
   
    if (x != 0x100B)
    {
    
        printf("  FAIL! testaddcommac() success test - expected 0x100B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommad\n");

    x = testaddcommad();
   
    if (x != 0x100C)
    {
    
        printf("  FAIL! testaddcommad() success test - expected 0x100C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommae\n");

    x = testaddcommae();
   
    if (x != 0x1122131477668641)
    {
    
        printf("  FAIL! testaddcommae() success test - expected 0x1122131477668641, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaf\n");

    x = testaddcommaf();
   
    if (x != 0x1122131477668642)
    {
    
        printf("  FAIL! testaddcommaf() success test - expected 0x1122131477668642, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommag\n");

    x = testaddcommag();
   
    if (x != 0x1122131477668643)
    {
    
        printf("  FAIL! testaddcommag() success test - expected 0x1122131477668643, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testadccommaa\n");

    x = testadccommaa();
   
    if (x != 0x300A)
    {
    
        printf("  FAIL! testadccommaa() success test - expected 0x300A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsbccommaa\n");

    x = testsbccommaa();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testsbccommaa() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsdivcommaa\n");

    x = testsdivcommaa();
   
    if (x != -0x7)
    {
    
        printf("  FAIL! testsdivcommaa() success test - expected -0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testasrcommaa\n");

    x = testasrcommaa();
   
    if (x != 0xE000000000000000)
    {
    
        printf("  FAIL! testasrcommaa() success test - expected 0xE000000000000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testlsrcommaa\n");

    x = testlsrcommaa();
   
    if (x != 0x2000000000000000)
    {
    
        printf("  FAIL! testlsrcommaa() success test - expected 0x2000000000000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmulcommaa\n");

    x = testmulcommaa();
   
    if (x != -0xF)
    {
    
        printf("  FAIL! testmulcommaa() success test - expected -0xF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testudivcommaa\n");

    x = testudivcommaa();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testudivcommaa() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testlslcommaa\n");

    x = testlslcommaa();
   
    if (x != 0x4)
    {
    
        printf("  FAIL! testlslcommaa() success test - expected 0x4, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrorcommaa\n");

    x = testrorcommaa();
   
    if (x != 0x4000000000000000)
    {
    
        printf("  FAIL! testrorcommaa() success test - expected 0x4000000000000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testandcommaa\n");

    x = testandcommaa();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testandcommaa() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testorcommaa\n");

    x = testorcommaa();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testorcommaa() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testxorcommaa\n");

    x = testxorcommaa();
   
    if (x != 0x6)
    {
    
        printf("  FAIL! testxorcommaa() success test - expected 0x6, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnandcommaa\n");

    x = testnandcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFFE)
    {
    
        printf("  FAIL! testnandcommaa() success test - expected 0xFFFFFFFFFFFFFFFE, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnorcommaa\n");

    x = testnorcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFF8)
    {
    
        printf("  FAIL! testnorcommaa() success test - expected 0xFFFFFFFFFFFFFFF8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testxnorcommaa\n");

    x = testxnorcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFF9)
    {
    
        printf("  FAIL! testxnorcommaa() success test - expected 0xFFFFFFFFFFFFFFF9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbiccommaa\n");

    x = testbiccommaa();
   
    if (x != 0x2)
    {
    
        printf("  FAIL! testbiccommaa() success test - expected 0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testorncommaa\n");

    x = testorncommaa();
   
    if (x != 0xFFFFFFFFFFFFFFFB)
    {
    
        printf("  FAIL! testorncommaa() success test - expected 0xFFFFFFFFFFFFFFFB, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testumulhcommaa\n");

    x = testumulhcommaa();
   
    if (x != 0x7FFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testumulhcommaa() success test - expected 0x7FFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsmulhcommaa\n");

    x = testsmulhcommaa();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testsmulhcommaa() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testandcommab\n");

    x = testandcommab();
   
    if (x != 0x8372)
    {
    
        printf("  FAIL! testandcommab() success test - expected 0x8372, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommah\n");

    x = testaddcommah();
   
    if (x != 0x8373)
    {
    
        printf("  FAIL! testaddcommah() success test - expected 0x8373, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommai\n");

    x = testaddcommai();
   
    if (x != 0x8374)
    {
    
        printf("  FAIL! testaddcommai() success test - expected 0x8374, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaj\n");

    x = testaddcommaj();
   
    if (x != 0x8375)
    {
    
        printf("  FAIL! testaddcommaj() success test - expected 0x8375, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommak\n");

    x = testaddcommak();
   
    if (x != 0x48)
    {
    
        printf("  FAIL! testaddcommak() success test - expected 0x48, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommal\n");

    x = testaddcommal();
   
    if (x != 0x49)
    {
    
        printf("  FAIL! testaddcommal() success test - expected 0x49, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommam\n");

    x = testaddcommam();
   
    if (x != 0x4A)
    {
    
        printf("  FAIL! testaddcommam() success test - expected 0x4A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcomman\n");

    x = testaddcomman();
   
    if (x != 0x4B)
    {
    
        printf("  FAIL! testaddcomman() success test - expected 0x4B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommao\n");

    x = testaddcommao();
   
    if (x != 0x100020003000004A)
    {
    
        printf("  FAIL! testaddcommao() success test - expected 0x100020003000004A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommap\n");

    x = testaddcommap();
   
    if (x != 0x100020003000004B)
    {
    
        printf("  FAIL! testaddcommap() success test - expected 0x100020003000004B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaq\n");

    x = testaddcommaq();
   
    if (x != 0x1123131677698644)
    {
    
        printf("  FAIL! testaddcommaq() success test - expected 0x1123131677698644, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommar\n");

    x = testaddcommar();
   
    if (x != 0xEEDDECEB889979C0)
    {
    
        printf("  FAIL! testaddcommar() success test - expected 0xEEDDECEB889979C0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommas\n");

    x = testaddcommas();
   
    if (x != 0x9)
    {
    
        printf("  FAIL! testaddcommas() success test - expected 0x9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommat\n");

    x = testaddcommat();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommat() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommau\n");

    x = testaddcommau();
   
    if (x != 0x2CB2)
    {
    
        printf("  FAIL! testaddcommau() success test - expected 0x2CB2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsubcommaa\n");

    x = testsubcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testsubcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsubcommab\n");

    x = testsubcommab();
   
    if (x != 0x100020003)
    {
    
        printf("  FAIL! testsubcommab() success test - expected 0x100020003, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testsubcommac\n");

    x = testsubcommac();
   
    if (x != 0x100020004)
    {
    
        printf("  FAIL! testsubcommac() success test - expected 0x100020004, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusplusntoir64a\n");

    x = testir64plusplusntoir64a();
   
    if (x != 0x1000200030009)
    {
    
        printf("  FAIL! testir64plusplusntoir64a() success test - expected 0x1000200030009, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusplusntoir64b\n");

    x = testir64plusplusntoir64b();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testir64plusplusntoir64b() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusplusntoir64c\n");

    x = testir64plusplusntoir64c();
   
    if (x != 0x100020003000A)
    {
    
        printf("  FAIL! testir64plusplusntoir64a() success test - expected 0x100020003000A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64plusplusntoir64d\n");

    x = testir64plusplusntoir64d();
   
    if (x != 0x188)
    {
    
        printf("  FAIL! testir64plusplusntoir64d() success test - expected 0x188, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64thenplusplusntoir64a\n");

    x = testir64thenplusplusntoir64a();
   
    if (x != 0x111122223333BBBB)
    {
    
        printf("  FAIL! testir64thenplusplusntoir64a() success test - expected 0x111122223333BBBB, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64thenplusplusntoir64b\n");

    x = testir64thenplusplusntoir64b();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testir64thenplusplusntoir64b() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64thenplusplusntoir64c\n");

    x = testir64thenplusplusntoir64c();
   
    if (x != 0x111122223333CCCC)
    {
    
        printf("  FAIL! testir64thenplusplusntoir64c() success test - expected 0x111122223333CCCC, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64thenplusplusntoir64d\n");

    x = testir64thenplusplusntoir64d();
   
    if (x != 0x188)
    {
    
        printf("  FAIL! testir64thenplusplusntoir64d() success test - expected 0x188, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64plusplusna\n");

    x = testir64toir64plusplusna();
   
    if (x != 0x1000200040001)
    {
    
        printf("  FAIL! testir64toir64plusplusna() success test - expected 0x1000200040001, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64plusplusnb\n");

    x = testir64toir64plusplusnb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testir64toir64plusplusnb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64plusplusnc\n");

    x = testir64toir64plusplusnc();
   
    if (x != 0x1000200050001)
    {
    
        printf("  FAIL! testir64toir64plusplusnc() success test - expected 0x1000200050001, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64plusplusnd\n");

    x = testir64toir64plusplusnd();
   
    if (x != 0x188)
    {
    
        printf("  FAIL! testir64toir64plusplusnd() success test - expected 0x188, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64thenplusplusna\n");

    x = testir64toir64thenplusplusna();
   
    if (x != 0x1000200060001)
    {
    
        printf("  FAIL! testir64toir64thenplusplusna() success test - expected 0x1000200060001, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64thenplusplusnb\n");

    x = testir64toir64thenplusplusnb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testir64toir64thenplusplusnb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64thenplusplusnc\n");

    x = testir64toir64thenplusplusnc();
   
    if (x != 0x1000200070001)
    {
    
        printf("  FAIL! testir64toir64thenplusplusnc() success test - expected 0x1000200070001, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testir64toir64thenplusplusnd\n");

    x = testir64toir64thenplusplusnd();
   
    if (x != 0x188)
    {
    
        printf("  FAIL! testir64toir64thenplusplusnd() success test - expected 0x188, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommav\n");

    x = testaddcommav();
   
    if (x != 0x7432)
    {
    
        printf("  FAIL! testaddcommav() success test - expected 0x7432, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaw\n");

    x = testaddcommaw();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommaw() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommax\n");

    x = testaddcommax();
   
    if (x != 0x7433)
    {
    
        printf("  FAIL! testaddcommax() success test - expected 0x7433, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommay\n");

    x = testaddcommay();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommay() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaz\n");

    x = testaddcommaz();
   
    if (x != 0x375A)
    {
    
        printf("  FAIL! testaddcommaz() success test - expected 0x375A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaaa\n");

    x = testaddcommaaa();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommaaa() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaab\n");

    x = testaddcommaab();
   
    if (x != 0x385A)
    {
    
        printf("  FAIL! testaddcommaab() success test - expected 0x375A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaac\n");

    x = testaddcommaac();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommaac() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaad\n");

    x = testaddcommaad();
   
    if (x != 0x495A)
    {
    
        printf("  FAIL! testaddcommaad() success test - expected 0x495A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaae\n");

    x = testaddcommaae();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommaae() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaaf\n");

    x = testaddcommaaf();
   
    if (x != 0x595A)
    {
    
        printf("  FAIL! testaddcommaaf() success test - expected 0x595A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaag\n");

    x = testaddcommaag();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testaddcommaag() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrbimma\n");

    x = testarmldrbimma();
   
    if (x != 0x84)
    {
    
        printf("  FAIL! testarmldrbimma() success test - expected 0x84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrhimma\n");

    x = testarmldrhimma();
   
    if (x != 0x8384)
    {
    
        printf("  FAIL! testarmldrhimma() success test - expected 0x8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrwimma\n");

    x = testarmldrwimma();
   
    if (x != 0x81828384)
    {
    
        printf("  FAIL! testarmldrwimma() success test - expected 0x81828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrximma\n");

    x = testarmldrximma();
   
    if (x != 0x0102030481828384)
    {
    
        printf("  FAIL! testarmldrximma() success test - expected 0x0102030481828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrsbwimma\n");

    x = testarmldrsbwimma();
   
    if (x != 0xFFFFFF84)
    {
    
        printf("  FAIL! testarmldrsbwimma() success test - expected 0xFFFFFF84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrsbximma\n");

    x = testarmldrsbximma();
   
    if (x != 0xFFFFFFFFFFFFFF84)
    {
    
        printf("  FAIL! testarmldrsbximma() success test - expected 0xFFFFFFFFFFFFFF84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrshwimma\n");

    x = testarmldrshwimma();
   
    if (x != 0xFFFF8384)
    {
    
        printf("  FAIL! testarmldrshwimma() success test - expected 0xFFFF8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrshximma\n");

    x = testarmldrshximma();
   
    if (x != 0xFFFFFFFFFFFF8384)
    {
    
        printf("  FAIL! testarmldrshximma() success test - expected 0xFFFFFFFFFFFF8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrswximma\n");

    x = testarmldrswximma();
   
    if (x != 0xFFFFFFFF81828384)
    {
    
        printf("  FAIL! testarmldrswximma() success test - expected 0xFFFFFFFF81828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrbimmplusplusa\n");

    x = testarmldrbimmplusplusa();
   
    if (x != 0x84)
    {
    
        printf("  FAIL! testarmldrbimmplusplusa() success test - expected 0x84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrbimmplusplusb\n");

    x = testarmldrbimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmldrbimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrhimmplusplusa\n");

    x = testarmldrhimmplusplusa();
   
    if (x != 0x8384)
    {
    
        printf("  FAIL! testarmldrhimmplusplusa() success test - expected 0x8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrhimmplusplusb\n");

    x = testarmldrhimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmldrhimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrwimmplusplusa\n");

    x = testarmldrwimmplusplusa();
   
    if (x != 0x81828384)
    {
    
        printf("  FAIL! testarmldrwimmplusplusa() success test - expected 0x81828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrwimmplusplusb\n");

    x = testarmldrwimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmldrwimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrximmplusplusa\n");

    x = testarmldrximmplusplusa();
   
    if (x != 0x0102030481828384)
    {
    
        printf("  FAIL! testarmldrximmplusplusa() success test - expected 0x0102030481828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrximmplusplusb\n");

    x = testarmldrximmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmldrximmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrba\n");

    x = testarmimmplusplusldrba();
   
    if (x != 0x84)
    {
    
        printf("  FAIL! testarmimmplusplusldrba() success test - expected 0x84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrbb\n");

    x = testarmimmplusplusldrbb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrbb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrha\n");

    x = testarmimmplusplusldrha();
   
    if (x != 0x8384)
    {
    
        printf("  FAIL! testarmimmplusplusldrha() success test - expected 0x8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrhb\n");

    x = testarmimmplusplusldrhb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrhb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrwa\n");

    x = testarmimmplusplusldrwa();
   
    if (x != 0x81828384)
    {
    
        printf("  FAIL! testarmimmplusplusldrwa() success test - expected 0x81828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrwb\n");

    x = testarmimmplusplusldrwb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrwb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrxa\n");

    x = testarmimmplusplusldrxa();
   
    if (x != 0x0102030481828384)
    {
    
        printf("  FAIL! testarmimmplusplusldrxa() success test - expected 0x0102030481828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrxb\n");

    x = testarmimmplusplusldrxb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrxb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmstrbimma\n");

    x = testarmstrbimma();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testarmstrbimma() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrhimma\n");

    x = testarmstrhimma();
   
    if (x != 0xFFFFFFFFFFFF7788)
    {
    
        printf("  FAIL! testarmstrhimma() success test - expected 0xFFFFFFFFFFFF7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrwimma\n");

    x = testarmstrwimma();
   
    if (x != 0xFFFFFFFF55667788)
    {
    
        printf("  FAIL! testarmstrwimma() success test - expected 0xFFFFFFFF55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrximma\n");

    x = testarmstrximma();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmstrximma() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmimmplusplusldrsbwa\n");

    x = testarmimmplusplusldrsbwa();
   
    if (x != 0xFFFFFF84)
    {
    
        printf("  FAIL! testarmimmplusplusldrsbwa() success test - expected 0xFFFFFF84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrsbwb\n");

    x = testarmimmplusplusldrsbwb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrsbwb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrsbxa\n");

    x = testarmimmplusplusldrsbxa();
   
    if (x != 0xFFFFFFFFFFFFFF84)
    {
    
        printf("  FAIL! testarmimmplusplusldrsbxa() success test - expected 0xFFFFFFFFFFFFFF84, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrsbxb\n");

    x = testarmimmplusplusldrsbxb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrsbxb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrshwa\n");

    x = testarmimmplusplusldrshwa();
   
    if (x != 0xFFFF8384)
    {
    
        printf("  FAIL! testarmimmplusplusldrshwa() success test - expected 0xFFFF8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrshwb\n");

    x = testarmimmplusplusldrshwb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrshwb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrshxa\n");

    x = testarmimmplusplusldrshxa();
   
    if (x != 0xFFFFFFFFFFFF8384)
    {
    
        printf("  FAIL! testarmimmplusplusldrshxa() success test - expected 0xFFFFFFFFFFFF8384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrshxb\n");

    x = testarmimmplusplusldrshxb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrshxb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrswxa\n");

    x = testarmimmplusplusldrswxa();
   
    if (x != 0xFFFFFFFF81828384)
    {
    
        printf("  FAIL! testarmimmplusplusldrswxa() success test - expected 0xFFFFFFFF81828384, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldrswxb\n");

    x = testarmimmplusplusldrswxb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusldrswxb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmimmplusplusstrba\n");

    x = testarmimmplusplusstrba();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testarmimmplusplusstrba() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrbb\n");

    x = testarmimmplusplusstrbb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusstrbb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrha\n");

    x = testarmimmplusplusstrha();
   
    if (x != 0xFFFFFFFFFFFF7788)
    {
    
        printf("  FAIL! testarmimmplusplusstrha() success test - expected 0xFFFFFFFFFFFF7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrhb\n");

    x = testarmimmplusplusstrhb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusstrhb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrwa\n");

    x = testarmimmplusplusstrwa();
   
    if (x != 0xFFFFFFFF55667788)
    {
    
        printf("  FAIL! testarmimmplusplusstrwa() success test - expected 0xFFFFFFFF55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrwb\n");

    x = testarmimmplusplusstrwb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusstrwb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrxa\n");

    x = testarmimmplusplusstrxa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmimmplusplusstrxa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstrxb\n");

    x = testarmimmplusplusstrxb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmimmplusplusstrxb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmstrbimmplusplusa\n");

    x = testarmstrbimmplusplusa();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testarmstrbimmplusplusa() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrbimmplusplusb\n");

    x = testarmstrbimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmstrbimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrhimmplusplusa\n");

    x = testarmstrhimmplusplusa();
   
    if (x != 0xFFFFFFFFFFFF7788)
    {
    
        printf("  FAIL! testarmstrhimmplusplusa() success test - expected 0xFFFFFFFFFFFF7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrhimmplusplusb\n");

    x = testarmstrhimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmstrhimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrwimmplusplusa\n");

    x = testarmstrwimmplusplusa();
   
    if (x != 0xFFFFFFFF55667788)
    {
    
        printf("  FAIL! testarmstrwimmplusplusa() success test - expected 0xFFFFFFFF55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrwimmplusplusb\n");

    x = testarmstrwimmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmstrwimmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrximmplusplusa\n");

    x = testarmstrximmplusplusa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmstrximmplusplusa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrximmplusplusb\n");

    x = testarmstrximmplusplusb();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testarmstrximmplusplusb() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrbrega\n");

    x = testarmldrbrega();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testarmldrbrega() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrhrega\n");

    x = testarmldrhrega();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testarmldrhrega() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrwrega\n");

    x = testarmldrwrega();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testarmldrwrega() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrxrega\n");

    x = testarmldrxrega();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testarmldrxrega() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmldrsbwrega\n");

    x = testarmldrsbwrega();
   
    if (x != 0xFFFFFF88)
    {
    
        printf("  FAIL! testarmldrsbwrega() success test - expected 0xFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrsbxrega\n");

    x = testarmldrsbxrega();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testarmldrsbxrega() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrshwrega\n");

    x = testarmldrshwrega();
   
    if (x != 0xFFFF8788)
    {
    
        printf("  FAIL! testarmldrshwrega() success test - expected 0xFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrshxrega\n");

    x = testarmldrshxrega();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testarmldrshxrega() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrswxrega\n");

    x = testarmldrswxrega();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testarmldrswxrega() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrbrega\n");

    x = testarmstrbrega();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testarmstrbrega() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrhrega\n");

    x = testarmstrhrega();
   
    if (x != 0xFFFFFFFFFFFF7788)
    {
    
        printf("  FAIL! testarmstrhrega() success test - expected 0xFFFFFFFFFFFF7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrwrega\n");

    x = testarmstrwrega();
   
    if (x != 0xFFFFFFFF55667788)
    {
    
        printf("  FAIL! testarmstrwrega() success test - expected 0xFFFFFFFF55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstrxrega\n");

    x = testarmstrxrega();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmstrxrega() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldrswlita\n");

    x = testarmldrswlita();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testarmldrswlita() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbnza\n");

    x = testarmcbnza();
   
    if (x != 0x1823)
    {
    
        printf("  FAIL! testarmcbnza() success test - expected 0x1823, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbnzb\n");

    x = testarmcbnzb();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testarmcbnzb() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbza\n");

    x = testarmcbza();
   
    if (x != 0x1824)
    {
    
        printf("  FAIL! testarmcbza() success test - expected 0x1824, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbzb\n");

    x = testarmcbzb();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmcbzb() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusir64toirsza\n");

    x = testbracketir64plusir64toirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64plusir64toirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusir64toirszb\n");

    x = testbracketir64plusir64toirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64plusir64toirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusir64a\n");

    x = testirsztobracketir64plusir64a();
   
    if (x != 0xFFFFFFFFFFFFFF28)
    {
    
        printf("  FAIL! testirsztobracketir64plusir64a() success test - expected 0xFFFFFFFFFFFFFF28, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toirsza\n");

    x = testbracketir64toirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64toirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64toirszb\n");

    x = testbracketir64toirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64toirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64a\n");

    x = testirsztobracketir64a();
   
    if (x != 0xFFFFFFFFFFFFFF29)
    {
    
        printf("  FAIL! testirsztobracketir64a() success test - expected 0xFFFFFFFFFFFFFF29, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirsza\n");

    x = testbracketir64plusntoirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64plusntoirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszb\n");

    x = testbracketir64plusntoirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64plusntoirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszc\n");

    x = testbracketir64plusntoirszc();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszc() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszd\n");

    x = testbracketir64plusntoirszd();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszd() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirsze\n");

    x = testbracketir64plusntoirsze();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirsze() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszf\n");

    x = testbracketir64plusntoirszf();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszf() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszg\n");

    x = testbracketir64plusntoirszg();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszg() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testbracketir64plusntoirszh\n");

    x = testbracketir64plusntoirszh();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64plusntoirszh() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszi\n");

    x = testbracketir64plusntoirszi();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64plusntoirszi() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszj\n");

    x = testbracketir64plusntoirszj();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszj() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszk\n");

    x = testbracketir64plusntoirszk();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszk() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszl\n");

    x = testbracketir64plusntoirszl();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszl() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszm\n");

    x = testbracketir64plusntoirszm();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszm() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusntoirszn\n");

    x = testbracketir64plusntoirszn();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64plusntoirszn() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    
    printf("  testing testirsztobracketir64plusna\n");

    x = testirsztobracketir64plusna();
   
    if (x != 0xFFFFFFFFFFFFFFC8)
    {
    
        printf("  FAIL! testirsztobracketir64plusna() success test - expected 0xFFFFFFFFFFFFFFC8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusnb\n");

    x = testirsztobracketir64plusnb();
   
    if (x != 0xFFFFFFFFFFFFFFC8)
    {
    
        printf("  FAIL! testirsztobracketir64plusnb() success test - expected 0xFFFFFFFFFFFFFFC8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusnc\n");

    x = testirsztobracketir64plusnc();
   
    if (x != 0xFFFFFFFFFFFFC7C8)
    {
    
        printf("  FAIL! testirsztobracketir64plusnc() success test - expected 0xFFFFFFFFFFFFC7C8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusnd\n");

    x = testirsztobracketir64plusnd();
   
    if (x != 0xFFFFFFFFFFFFC7C8)
    {
    
        printf("  FAIL! testirsztobracketir64plusnd() success test - expected 0xFFFFFFFFFFFFC7C8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusne\n");

    x = testirsztobracketir64plusne();
   
    if (x != 0xFFFFFFFFC5C6C7C8)
    {
    
        printf("  FAIL! testirsztobracketir64plusne() success test - expected 0xFFFFFFFFC5C6C7C8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusnf\n");

    x = testirsztobracketir64plusnf();
   
    if (x != 0xFFFFFFFFC5C6C7C8)
    {
    
        printf("  FAIL! testirsztobracketir64plusnf() success test - expected 0xFFFFFFFFC5C6C7C8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusng\n");

    x = testirsztobracketir64plusng();
   
    if (x != 0xC1C2C3C4C5C6C7C8)
    {
    
        printf("  FAIL! testirsztobracketir64plusng() success test - expected 0xC1C2C3C4C5C6C7C8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    
    printf("  testing testbracketpcplusntoirsza\n");

    x = testbracketpcplusntoirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketpcplusntoirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirszb\n");

    x = testbracketpcplusntoirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketpcplusntoirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirszc\n");

    x = testbracketpcplusntoirszc();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketpcplusntoirszc() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirszd\n");

    x = testbracketpcplusntoirszd();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketpcplusntoirszd() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirsze\n");

    x = testbracketpcplusntoirsze();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketpcplusntoirsze() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirszf\n");

    x = testbracketpcplusntoirszf();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketpcplusntoirszf() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketpcplusntoirszg\n");

    x = testbracketpcplusntoirszg();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketpcplusntoirszg() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketotoirsza\n");

    x = testbracketotoirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketotoirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testbracketir64plusplusntoirsza\n");

    x = testbracketir64plusplusntoirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirsza2\n");

    x = testbracketir64plusplusntoirsza2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirsza2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszb\n");

    x = testbracketir64plusplusntoirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszb2\n");

    x = testbracketir64plusplusntoirszb2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszb2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszc\n");

    x = testbracketir64plusplusntoirszc();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszc() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszc2\n");

    x = testbracketir64plusplusntoirszc2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszc2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszd\n");

    x = testbracketir64plusplusntoirszd();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszd() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszd2\n");

    x = testbracketir64plusplusntoirszd2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszd2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirsze\n");

    x = testbracketir64plusplusntoirsze();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirsze() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirsze2\n");

    x = testbracketir64plusplusntoirsze2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirsze2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszf\n");

    x = testbracketir64plusplusntoirszf();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszf() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszf2\n");

    x = testbracketir64plusplusntoirszf2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszf2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszg\n");

    x = testbracketir64plusplusntoirszg();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszg() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszg2\n");

    x = testbracketir64plusplusntoirszg2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszg2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszh\n");

    x = testbracketir64plusplusntoirszh();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszh() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszh2\n");

    x = testbracketir64plusplusntoirszh2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszh2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszi\n");

    x = testbracketir64plusplusntoirszi();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszi() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszi2\n");

    x = testbracketir64plusplusntoirszi2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszi2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszj\n");

    x = testbracketir64plusplusntoirszj();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszj() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszj2\n");

    x = testbracketir64plusplusntoirszj2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszj2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszk\n");

    x = testbracketir64plusplusntoirszk();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszk() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszk2\n");

    x = testbracketir64plusplusntoirszk2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszk2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszl\n");

    x = testbracketir64plusplusntoirszl();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszl() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszl2\n");

    x = testbracketir64plusplusntoirszl2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszl2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszm\n");

    x = testbracketir64plusplusntoirszm();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszm() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszm2\n");

    x = testbracketir64plusplusntoirszm2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszm2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszn\n");

    x = testbracketir64plusplusntoirszn();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszn() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64plusplusntoirszn2\n");

    x = testbracketir64plusplusntoirszn2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64plusplusntoirszn2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testbracketir64thenplusplusntoirsza\n");

    x = testbracketir64thenplusplusntoirsza();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirsza() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirsza2\n");

    x = testbracketir64thenplusplusntoirsza2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirsza2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszb\n");

    x = testbracketir64thenplusplusntoirszb();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszb() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszb2\n");

    x = testbracketir64thenplusplusntoirszb2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszb2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszc\n");

    x = testbracketir64thenplusplusntoirszc();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszc() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszc2\n");

    x = testbracketir64thenplusplusntoirszc2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszc2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszd\n");

    x = testbracketir64thenplusplusntoirszd();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszd() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszd2\n");

    x = testbracketir64thenplusplusntoirszd2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszd2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirsze\n");

    x = testbracketir64thenplusplusntoirsze();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirsze() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirsze2\n");

    x = testbracketir64thenplusplusntoirsze2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirsze2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszf\n");

    x = testbracketir64thenplusplusntoirszf();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszf() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszf2\n");

    x = testbracketir64thenplusplusntoirszf2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszf2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszg\n");

    x = testbracketir64thenplusplusntoirszg();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszg() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszg2\n");

    x = testbracketir64thenplusplusntoirszg2();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszg2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszh\n");

    x = testbracketir64thenplusplusntoirszh();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszh() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszh2\n");

    x = testbracketir64thenplusplusntoirszh2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszh2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszi\n");

    x = testbracketir64thenplusplusntoirszi();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszi() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszi2\n");

    x = testbracketir64thenplusplusntoirszi2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszi2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszj\n");

    x = testbracketir64thenplusplusntoirszj();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszj() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszj2\n");

    x = testbracketir64thenplusplusntoirszj2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszj2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszk\n");

    x = testbracketir64thenplusplusntoirszk();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszk() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszk2\n");

    x = testbracketir64thenplusplusntoirszk2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszk2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszl\n");

    x = testbracketir64thenplusplusntoirszl();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszl() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszl2\n");

    x = testbracketir64thenplusplusntoirszl2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszl2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszm\n");

    x = testbracketir64thenplusplusntoirszm();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszm() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszm2\n");

    x = testbracketir64thenplusplusntoirszm2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszm2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszn\n");

    x = testbracketir64thenplusplusntoirszn();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszn() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketir64thenplusplusntoirszn2\n");

    x = testbracketir64thenplusplusntoirszn2();
   
    if (x != 0x10010)
    {
    
        printf("  FAIL! testbracketir64thenplusplusntoirszn2() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testirsztobracketir64plusplusna\n");

    x = testirsztobracketir64plusplusna();
   
    if (x != 0xffffffffffffff88)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusna() success test - expected 0xffffffffffffff88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusna2\n");

    x = testirsztobracketir64plusplusna2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusna2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnb\n");

    x = testirsztobracketir64plusplusnb();
   
    if (x != 0xffffffffffff7788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnb() success test - expected 0xffffffffffff7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnb2\n");

    x = testirsztobracketir64plusplusnb2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnb2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnc\n");

    x = testirsztobracketir64plusplusnc();
   
    if (x != 0xffffffff55667788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnc() success test - expected 0xffffffff55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnc2\n");

    x = testirsztobracketir64plusplusnc2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnc2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnd\n");

    x = testirsztobracketir64plusplusnd();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnd() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnd2\n");

    x = testirsztobracketir64plusplusnd2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnd2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusne\n");

    x = testirsztobracketir64plusplusne();
   
    if (x != 0xffffffffffffff88)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusne() success test - expected 0xffffffffffffff88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusne2\n");

    x = testirsztobracketir64plusplusne2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusne2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnf\n");

    x = testirsztobracketir64plusplusnf();
   
    if (x != 0xffffffffffff7788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnf() success test - expected 0xffffffffffff7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnf2\n");

    x = testirsztobracketir64plusplusnf2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnf2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusng\n");

    x = testirsztobracketir64plusplusng();
   
    if (x != 0xffffffff55667788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusng() success test - expected 0xffffffff55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusng2\n");

    x = testirsztobracketir64plusplusng2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusng2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnh\n");

    x = testirsztobracketir64plusplusnh();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnh() success test - expected 00x1122334455667788x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64plusplusnh2\n");

    x = testirsztobracketir64plusplusnh2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64plusplusnh2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testirsztobracketir64thenplusplusna\n");

    x = testirsztobracketir64thenplusplusna();
   
    if (x != 0xffffffffffffff88)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusna() success test - expected 0xffffffffffffff88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusna2\n");

    x = testirsztobracketir64thenplusplusna2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusna2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnb\n");

    x = testirsztobracketir64thenplusplusnb();
   
    if (x != 0xffffffffffff7788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnb() success test - expected 0xffffffffffff7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnb2\n");

    x = testirsztobracketir64thenplusplusnb2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnb2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnc\n");

    x = testirsztobracketir64thenplusplusnc();
   
    if (x != 0xffffffff55667788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnc() success test - expected 0xffffffff55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnc2\n");

    x = testirsztobracketir64thenplusplusnc2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnc2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnd\n");

    x = testirsztobracketir64thenplusplusnd();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnd() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnd2\n");

    x = testirsztobracketir64thenplusplusnd2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnd2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusne\n");

    x = testirsztobracketir64thenplusplusne();
   
    if (x != 0xffffffffffffff88)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusne() success test - expected 0xffffffffffffff88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusne2\n");

    x = testirsztobracketir64thenplusplusne2();
   
    if (x != 0x1000)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusne2() success test - expected 0x1000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnf\n");

    x = testirsztobracketir64thenplusplusnf();
   
    if (x != 0xffffffffffff7788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnf() success test - expected 0xffffffffffff7788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnf2\n");

    x = testirsztobracketir64thenplusplusnf2();
   
    if (x != 0x1000)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnf2() success test - expected 0x1000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusng\n");

    x = testirsztobracketir64thenplusplusng();
   
    if (x != 0xffffffff55667788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusng() success test - expected 0xffffffff55667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusng2\n");

    x = testirsztobracketir64thenplusplusng2();
   
    if (x != 0x1000)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusng2() success test - expected 0x1000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnh\n");

    x = testirsztobracketir64thenplusplusnh();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnh() success test - expected 00x1122334455667788x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketir64thenplusplusnh2\n");

    x = testirsztobracketir64thenplusplusnh2();
   
    if (x != 0x1000)
    {
    
        printf("  FAIL! testirsztobracketir64thenplusplusnh2() success test - expected 0x1000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testbracketrspplusntoirsza\n");

    x = testbracketrspplusntoirsza();
   
    if (x != 0xD7D8)
    {
    
        printf("  FAIL! testbracketrspplusntoirsza() success test - expected 0xD7D8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztobracketrspplusna\n");

    x = testirsztobracketrspplusna();
   
    if (x != 0xFFFFFFFFFFFFE7E8)
    {
    
        printf("  FAIL! testirsztobracketrspplusna() success test - expected 0xFFFFFFFFFFFFE7E8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testmatoscratchreg2sza\n");

    x = testmatoscratchreg2sza();
   
    if (x != 0x39)
    {
    
        printf("  FAIL! testmatoscratchreg2sza() success test - expected 0x39, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szb\n");

    x = testmatoscratchreg2szb();
   
    if (x != 0x49)
    {
    
        printf("  FAIL! testmatoscratchreg2szb() success test - expected 0x49, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szc\n");

    x = testmatoscratchreg2szc();
   
    if (x != 0x40)
    {
    
        printf("  FAIL! testmatoscratchreg2szc() success test - expected 0x40, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szd\n");

    x = testmatoscratchreg2szd();
   
    if (x != 0x55)
    {
    
        printf("  FAIL! testmatoscratchreg2szd() success test - expected 0x55, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2sze\n");

    x = testmatoscratchreg2sze();
   
    if (x != 0x59)
    {
    
        printf("  FAIL! testmatoscratchreg2sze() success test - expected 0x59, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szf\n");

    x = testmatoscratchreg2szf();
   
    if (x != 0x69)
    {
    
        printf("  FAIL! testmatoscratchreg2szf() success test - expected 0x69, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szg\n");

    x = testmatoscratchreg2szg();
   
    if (x != 0x30)
    {
    
        printf("  FAIL! testmatoscratchreg2szg() success test - expected 0x30, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szh\n");

    x = testmatoscratchreg2szh();
   
    if (x != 0x5C)
    {
    
        printf("  FAIL! testmatoscratchreg2szh() success test - expected 0x5C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szh2\n");

    x = testmatoscratchreg2szh2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testmatoscratchreg2szh2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szi\n");

    x = testmatoscratchreg2szi();
   
    if (x != 0x3C)
    {
    
        printf("  FAIL! testmatoscratchreg2szi() success test - expected 0x3C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmatoscratchreg2szi2\n");

    x = testmatoscratchreg2szi2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testmatoscratchreg2szi2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testmbtoscratchreg1sza\n");

    x = testmbtoscratchreg1sza();
   
    if (x != 0x39)
    {
    
        printf("  FAIL! testmbtoscratchreg1sza() success test - expected 0x39, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szb\n");

    x = testmbtoscratchreg1szb();
   
    if (x != 0x49)
    {
    
        printf("  FAIL! testmbtoscratchreg1szb() success test - expected 0x49, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szc\n");

    x = testmbtoscratchreg1szc();
   
    if (x != 0x40)
    {
    
        printf("  FAIL! testmbtoscratchreg1szc() success test - expected 0x40, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szd\n");

    x = testmbtoscratchreg1szd();
   
    if (x != 0x55)
    {
    
        printf("  FAIL! testmbtoscratchreg1szd() success test - expected 0x55, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1sze\n");

    x = testmbtoscratchreg1sze();
   
    if (x != 0x59)
    {
    
        printf("  FAIL! testmbtoscratchreg1sze() success test - expected 0x59, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szf\n");

    x = testmbtoscratchreg1szf();
   
    if (x != 0x69)
    {
    
        printf("  FAIL! testmbtoscratchreg1szf() success test - expected 0x69, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szg\n");

    x = testmbtoscratchreg1szg();
   
    if (x != 0x30)
    {
    
        printf("  FAIL! testmbtoscratchreg1szg() success test - expected 0x30, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szh\n");

    x = testmbtoscratchreg1szh();
   
    if (x != 0x5D)
    {
    
        printf("  FAIL! testmbtoscratchreg1szh() success test - expected 0x5D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szh2\n");

    x = testmbtoscratchreg1szh2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testmbtoscratchreg1szh2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szi\n");

    x = testmbtoscratchreg1szi();
   
    if (x != 0x3F)
    {
    
        printf("  FAIL! testmbtoscratchreg1szi() success test - expected 0x3F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmbtoscratchreg1szi2\n");

    x = testmbtoscratchreg1szi2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testmbtoscratchreg1szi2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testscratchreg2sztomdesta\n");

    x = testscratchreg2sztomdesta();
   
    if (x != 0x1282)
    {
    
        printf("  FAIL! testscratchreg2sztomdesta() success test - expected 0x1282, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdestb\n");

    x = testscratchreg2sztomdestb();
   
    if (x != 0x1392)
    {
    
        printf("  FAIL! testscratchreg2sztomdestb() success test - expected 0x1392, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdestc\n");

    x = testscratchreg2sztomdestc();
   
    if (x != 0x15A2)
    {
    
        printf("  FAIL! testscratchreg2sztomdestc() success test - expected 0x15A2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdestd\n");

    x = testscratchreg2sztomdestd();
   
    if (x != 0x1493)
    {
    
        printf("  FAIL! testscratchreg2sztomdestd() success test - expected 0x1493, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdestd2\n");

    x = testscratchreg2sztomdestd2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testscratchreg2sztomdestd2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdeste\n");

    x = testscratchreg2sztomdeste();
   
    if (x != 0x3294)
    {
    
        printf("  FAIL! testscratchreg2sztomdeste() success test - expected 0x3294, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testscratchreg2sztomdeste2\n");

    x = testscratchreg2sztomdeste2();
   
    if (x != 0x8)
    {
    
        printf("  FAIL! testscratchreg2sztomdeste2() success test - expected 0x8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testbracketr8bitrtoraddcomma\n");

    x = testbracketr8bitrtoraddcomma();
   
    if (x != 0x0102030405060748)
    {
    
        printf("  FAIL! testbracketr8bitrtoraddcomma() success test - expected 0x0102030405060748, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrbracketr8bittoraddcomma\n");

    x = testrbracketr8bittoraddcomma();
   
    if (x != 0x0102030405060749)
    {
    
        printf("  FAIL! testrbracketr8bittoraddcomma() success test - expected 0x0102030405060749, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testrrtobracketr8bitaddcomma\n");

    x = testrrtobracketr8bitaddcomma();
   
    if (x != 0xFFFFFFFFFFFFFF33)
    {
    
        printf("  FAIL! testrrtobracketr8bitaddcomma() success test - expected 0xFFFFFFFFFFFFFF33, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test0negcomma\n");

    x = test0negcomma();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! test0negcomma() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test1negcomma\n");

    x = test1negcomma();
   
    if (x != -0x1)
    {
    
        printf("  FAIL! test0negcomma() success test - expected -0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test0notcomma\n");

    x = test0notcomma();
   
    if (x != -0x1)
    {
    
        printf("  FAIL! test0notcomma() success test - expected -0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test1notcomma\n");

    x = test1notcomma();
   
    if (x != -0x2)
    {
    
        printf("  FAIL! test1notcomma() success test - expected -0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test0inccomma\n");

    x = test0inccomma();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! test0inccomma() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test1inccomma\n");

    x = test1inccomma();
   
    if (x != 0x2)
    {
    
        printf("  FAIL! test1inccomma() success test - expected 0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test0deccomma\n");

    x = test0deccomma();
   
    if (x != -0x1)
    {
    
        printf("  FAIL! test0deccomma() success test - expected -0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing test1deccomma\n");

    x = test1deccomma();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! test1deccomma() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommaa\n");

    x = testmovcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testmovcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommab\n");

    x = testmovcommab();
   
    if (x != 0x3132333435363738)
    {
    
        printf("  FAIL! testmovcommab() success test - expected 0x3132333435363738, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommac\n");

    x = testmovcommac();
   
    if (x != 0x48)
    {
    
        printf("  FAIL! testmovcommac() success test - expected 0x48, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommad\n");

    x = testmovcommad();
   
    if (x != 0xFFFFFFFFFFFFFF98)
    {
    
        printf("  FAIL! testmovcommad() success test - expected 0xFFFFFFFFFFFFFF98, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommae\n");

    x = testmovcommae();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmovcommae() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommaf\n");

    x = testmovcommaf();
   
    if (x != 0xFFFFFFFFFFFF8640)
    {
    
        printf("  FAIL! testmovcommaf() success test - expected 0xFFFFFFFFFFFF8640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommag\n");

    x = testmovcommag();
   
    if (x != 0x1287932785028273)
    {
    
        printf("  FAIL! testmovcommag() success test - expected 0x1287932785028273, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommah\n");

    x = testmovcommah();
   
    if (x != 0xF0F0F0F085028273)
    {
    
        printf("  FAIL! testmovcommah() success test - expected 0xF0F0F0F085028273, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommai\n");

    x = testmovcommai();
   
    if (x != 0x1287932785028274)
    {
    
        printf("  FAIL! testmovcommai() success test - expected 0x1287932785028274, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommaj\n");

    x = testmovcommaj();
   
    if (x != 0xF0F0F0F0F0F0F075)
    {
    
        printf("  FAIL! testmovcommaj() success test - expected 0xF0F0F0F0F0F0F075, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommak\n");

    x = testmovcommak();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmovcommak() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommal\n");

    x = testmovcommal();
   
    if (x != 0x40)
    {
    
        printf("  FAIL! testmovcommal() success test - expected 0x40, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommam\n");

    x = testmovcommam();
   
    if (x != 0xF0F0F0F0F0F0F040)
    {
    
        printf("  FAIL! testmovcommam() success test - expected 0xF0F0F0F0F0F0F040, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcomman\n");

    x = testmovcomman();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmovcomman() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testmovcommao\n");

    x = testmovcommao();
   
    if (x != 0x1122131477668640)
    {
    
        printf("  FAIL! testmovcommao() success test - expected 0x1122131477668640, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64a\n");

    x = testirsztoir64a();
   
    if (x != 0x88)
    {
    
        printf("  FAIL! testirsztoir64a() success test - expected 0x88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64b\n");

    x = testirsztoir64b();
   
    if (x != 0x8788)
    {
    
        printf("  FAIL! testirsztoir64b() success test - expected 0x8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64c\n");

    x = testirsztoir64c();
   
    if (x != 0x85868788)
    {
    
        printf("  FAIL! testirsztoir64c() success test - expected 0x85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64d\n");

    x = testirsztoir64d();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testirsztoir64d() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64e\n");

    x = testirsztoir64e();
   
    if (x != 0xFFFFFFFFFFFFFF88)
    {
    
        printf("  FAIL! testirsztoir64e() success test - expected 0xFFFFFFFFFFFFFF88, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64f\n");

    x = testirsztoir64f();
   
    if (x != 0xFFFFFFFFFFFF8788)
    {
    
        printf("  FAIL! testirsztoir64f() success test - expected 0xFFFFFFFFFFFF8788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64g\n");

    x = testirsztoir64g();
   
    if (x != 0xFFFFFFFF85868788)
    {
    
        printf("  FAIL! testirsztoir64g() success test - expected 0xFFFFFFFF85868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64h\n");

    x = testirsztoir64h();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testirsztoir64h() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64i\n");

    x = testirsztoir64i();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testirsztoir64i() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testirsztoir64j\n");

    x = testirsztoir64j();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testirsztoir64j() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testr8bitntoraddcomma\n");

    x = testr8bitntoraddcomma();
   
    if (x != 0x8D)
    {
    
        printf("  FAIL! testr8bitntoraddcomma() success test - expected 0x8D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnr16bittoraddcomma\n");

    x = testnr16bittoraddcomma();
   
    if (x != 0x878E)
    {
    
        printf("  FAIL! testnr16bittoraddcomma() success test - expected 0x878E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testnrtor32bitaddcomma\n");

    x = testnrtor32bitaddcomma();
   
    if (x != 0x8586878F)
    {
    
        printf("  FAIL! testnrtor32bitaddcomma() success test - expected 0x8586878F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testtstcommaa\n");

    x = testtstcommaa();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testtstcommaa() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testtstcommab\n");

    x = testtstcommab();
   
    if (x != 0x4567)
    {
    
        printf("  FAIL! testtstcommab() success test - expected 0x4567, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testtstcommac\n");

    x = testtstcommac();
   
    if (x != 0x4568)
    {
    
        printf("  FAIL! testtstcommac() success test - expected 0x4568, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommaa\n");

    x = testcmpcommaa();
   
    if (x != 0x9)
    {
    
        printf("  FAIL! testcmpcommaa() success test - expected 0x9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommab\n");

    x = testcmpcommab();
   
    if (x != 0x4577)
    {
    
        printf("  FAIL! testcmpcommab() success test - expected 0x4577, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommac\n");

    x = testcmpcommac();
   
    if (x != 0x4578)
    {
    
        printf("  FAIL! testcmpcommac() success test - expected 0x4578, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommad\n");

    x = testcmpcommad();
   
    if (x != 0x4579)
    {
    
        printf("  FAIL! testcmpcommad() success test - expected 0x4579, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommae\n");

    x = testcmpcommae();
   
    if (x != 0x457A)
    {
    
        printf("  FAIL! testcmpcommae() success test - expected 0x457A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommaf\n");

    x = testcmpcommaf();
   
    if (x != 0x457B)
    {
    
        printf("  FAIL! testcmpcommaf() success test - expected 0x457B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommag\n");

    x = testcmpcommag();
   
    if (x != 0x457C)
    {
    
        printf("  FAIL! testcmpcommag() success test - expected 0x457C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommah\n");

    x = testcmpcommah();
   
    if (x != 0x457D)
    {
    
        printf("  FAIL! testcmpcommah() success test - expected 0x457D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testcmpcommai\n");

    x = testcmpcommai();
   
    if (x != 0x457E)
    {
    
        printf("  FAIL! testcmpcommai() success test - expected 0x457E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaai\n");

    x = testaddcommaai();
   
    if (x != 0x9988776652535455)
    {
    
        printf("  FAIL! testaddcommaai() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaaj\n");

    x = testaddcommaaj();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testaddcommaaj() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaak\n");

    x = testaddcommaak();
   
    if (x != 0x9988776652535455)
    {
    
        printf("  FAIL! testaddcommaak() success test - expected 0x9988776652535455, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testaddcommaal\n");

    x = testaddcommaal();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testaddcommaal() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadccommaa\n");

    x = testarmadccommaa();
   
    if (x != 0x6689)
    {
    
        printf("  FAIL! testarmadccommaa() success test - expected 0x6689, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadccommab\n");

    x = testarmadccommab();
   
    if (x != 0x6688)
    {
    
        printf("  FAIL! testarmadccommab() success test - expected 0x6688, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadcscommaa\n");

    x = testarmadcscommaa();
   
    if (x != 0x6667)
    {
    
        printf("  FAIL! testarmadcscommaa() success test - expected 0x6667, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadcscommab\n");

    x = testarmadcscommab();
   
    if (x != 0x9876)
    {
    
        printf("  FAIL! testarmadcscommab() success test - expected 0x9876, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmadcscommac\n");

    x = testarmadcscommac();
   
    if (x != 0x9877)
    {
    
        printf("  FAIL! testarmadcscommac() success test - expected 0x9877, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcascommaa\n");

    x = testarmcascommaa();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcascommaa() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcascommab\n");

    x = testarmcascommab();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcascommab() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcascommac\n");

    x = testarmcascommac();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcascommac() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasacommaa\n");

    x = testarmcasacommaa();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcasacommaa() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasacommab\n");

    x = testarmcasacommab();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcasacommab() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasalcommaa\n");

    x = testarmcasalcommaa();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcasalcommaa() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasalcommab\n");

    x = testarmcasalcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcasalcommab() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaslcommaa\n");

    x = testarmcaslcommaa();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcaslcommaa() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaslcommab\n");

    x = testarmcaslcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaslcommab() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspcommaa\n");

    x = testarmcaspcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcaspcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspcommab\n");

    x = testarmcaspcommab();
   
    if (x != 0x2122232425262728)
    {
    
        printf("  FAIL! testarmcaspcommab() success test - expected 0x2122232425262728, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspcommac\n");

    x = testarmcaspcommac();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspcommac() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspcommad\n");

    x = testarmcaspcommad();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcaspcommad() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspcommae\n");

    x = testarmcaspcommae();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspcommae() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspacommaa\n");

    x = testarmcaspacommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcaspacommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspacommab\n");

    x = testarmcaspacommab();
   
    if (x != 0x2122232425262728)
    {
    
        printf("  FAIL! testarmcaspacommab() success test - expected 0x2122232425262728, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspacommac\n");

    x = testarmcaspacommac();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspacommac() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspacommad\n");

    x = testarmcaspacommad();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcaspacommad() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspacommae\n");

    x = testarmcaspacommae();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspacommae() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspalcommaa\n");

    x = testarmcaspalcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcaspalcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspalcommab\n");

    x = testarmcaspalcommab();
   
    if (x != 0x2122232425262728)
    {
    
        printf("  FAIL! testarmcaspalcommab() success test - expected 0x2122232425262728, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspalcommac\n");

    x = testarmcaspalcommac();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspalcommac() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspalcommad\n");

    x = testarmcaspalcommad();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcaspalcommad() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspalcommae\n");

    x = testarmcaspalcommae();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcaspalcommae() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasplcommaa\n");

    x = testarmcasplcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcasplcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasplcommab\n");

    x = testarmcasplcommab();
   
    if (x != 0x2122232425262728)
    {
    
        printf("  FAIL! testarmcasplcommab() success test - expected 0x2122232425262728, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasplcommac\n");

    x = testarmcasplcommac();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcasplcommac() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasplcommad\n");

    x = testarmcasplcommad();
   
    if (x != 0x123456789ABCDEF0)
    {
    
        printf("  FAIL! testarmcasplcommad() success test - expected 0x123456789ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcasplcommae\n");

    x = testarmcasplcommae();
   
    if (x != 0xF0F0F0F0F0F0F0F0)
    {
    
        printf("  FAIL! testarmcasplcommae() success test - expected 0xF0F0F0F0F0F0F0F0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsetcommaa\n");

    x = testarmcsetcommaa();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testarmcsetcommaa() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsetcommab\n");

    x = testarmcsetcommab();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmcsetcommab() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsetmcommaa\n");

    x = testarmcsetmcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testarmcsetmcommaa() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsetmcommab\n");

    x = testarmcsetmcommab();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmcsetmcommab() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcselcommaa\n");

    x = testarmcselcommaa();
   
    if (x != 0x1234)
    {
    
        printf("  FAIL! testarmcselcommaa() success test - expected 0x1234, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcselcommab\n");

    x = testarmcselcommab();
   
    if (x != 0x5678)
    {
    
        printf("  FAIL! testarmcselcommab() success test - expected 0x5678, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclscommaa\n");

    x = testarmclscommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmclscommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclscommab\n");

    x = testarmclscommab();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testarmclscommab() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclscommac\n");

    x = testarmclscommac();
   
    if (x != 0x2)
    {
    
        printf("  FAIL! testarmclscommac() success test - expected 0x2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclscommad\n");

    x = testarmclscommad();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmclscommad() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclzcommaa\n");

    x = testarmclzcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmclzcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclzcommab\n");

    x = testarmclzcommab();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testarmclzcommab() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmclzcommac\n");

    x = testarmclzcommac();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmclzcommac() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }  

    printf("  testing testarmrbitcommaa\n");

    x = testarmrbitcommaa();
   
    if (x != 0x800F00FF0FFFFFFF)
    {
    
        printf("  FAIL! testarmrbitcommaa() success test - expected 0x800F00FF0FFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }  

    printf("  testing testarmrevcommaa\n");

    x = testarmrevcommaa();
   
    if (x != 0x100F00FF0FFFFFFF)
    {
    
        printf("  FAIL! testarmrevcommaa() success test - expected 0x100F00FF0FFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrev64commaa\n");

    x = testarmrev64commaa();
   
    if (x != 0x120F00FF0FFFFFFF)
    {
    
        printf("  FAIL! testarmrev64commaa() success test - expected 0x100F00FF0FFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrev32commaa\n");

    x = testarmrev32commaa();
   
    if (x != 0x0FFFFFFF130F00FF)
    {
    
        printf("  FAIL! testarmrev32commaa() success test - expected 0x0FFFFFFF130F00FF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrev16commaa\n");

    x = testarmrev16commaa();
   
    if (x != 0xFFFF0FFF00FF140F)
    {
    
        printf("  FAIL! testarmrev16commaa() success test - expected 0xFFFF0FFF00FF140F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldxpcommaa\n");

    x = testarmldxpcommaa();
   
    if (x != 0x123456789ABCDEF6)
    {
    
        printf("  FAIL! testarmldxpcommaa() success test - expected 0x123456789ABCDEF6, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldxpcommab\n");

    x = testarmldxpcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F5)
    {
    
        printf("  FAIL! testarmldxpcommab() success test - expected 0xF0F0F0F0F0F0F0F5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstxpcommaa\n");

    x = testarmstxpcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmstxpcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstxpcommab\n");

    x = testarmstxpcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F1)
    {
    
        printf("  FAIL! testarmstxpcommab() success test - expected 0xF0F0F0F0F0F0F0F1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstxpcommac\n");

    x = testarmstxpcommac();
   
    if (x != 0x123456789ABCDEF3)
    {
    
        printf("  FAIL! testarmstxpcommac() success test - expected 0x123456789ABCDEF3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstxpcommad\n");

    x = testarmstxpcommad();
   
    if (x != 0x1)
    {
    
        printf("  FAIL! testarmstxpcommad() success test - expected 0x1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpcommaa\n");

    x = testarmldpcommaa();
   
    if (x != 0x123456789ABCDEF8)
    {
    
        printf("  FAIL! testarmldpcommaa() success test - expected 0x123456789ABCDEF8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpcommab\n");

    x = testarmldpcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F7)
    {
    
        printf("  FAIL! testarmldpcommab() success test - expected 0xF0F0F0F0F0F0F0F7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpcommac\n");

    x = testarmldpcommac();
   
    if (x != 0x123456789ABCDEFA)
    {
    
        printf("  FAIL! testarmldpcommac() success test - expected 0x123456789ABCDEFA, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpcommad\n");

    x = testarmldpcommad();
   
    if (x != 0xF0F0F0F0F0F0F0F9)
    {
    
        printf("  FAIL! testarmldpcommad() success test - expected 0xF0F0F0F0F0F0F0F9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpimmpluspluscommaa\n");

    x = testarmldpimmpluspluscommaa();
   
    if (x != 0x123456789ABCDEF2)
    {
    
        printf("  FAIL! testarmldpimmpluspluscommaa() success test - expected 0x123456789ABCDEF2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpimmpluspluscommab\n");

    x = testarmldpimmpluspluscommab();
   
    if (x != 0xF0F0F0F0F0F0F0F1)
    {
    
        printf("  FAIL! testarmldpimmpluspluscommab() success test - expected 0xF0F0F0F0F0F0F0F1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldpimmpluspluscommac\n");

    x = testarmldpimmpluspluscommac();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testarmldpimmpluspluscommac() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsinca\n");

    x = testarmcsinca();
   
    if (x != 0x8182838485868788)
    {
    
        printf("  FAIL! testarmcsinca() success test - expected 0x8182838485868788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsincb\n");

    x = testarmcsincb();
   
    if (x != 0x1315171921232528)
    {
    
        printf("  FAIL! testarmcsincb() success test - expected 0x1315171921232528, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsinva\n");

    x = testarmcsinva();
   
    if (x != 0x8182838485868789)
    {
    
        printf("  FAIL! testarmcsinva() success test - expected 0x8182838485868789, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsinvb\n");

    x = testarmcsinvb();
   
    if (x != 0xECEAE8E6DEDCDAD8)
    {
    
        printf("  FAIL! testarmcsinvb() success test - expected 0xECEAE8E6DEDCDAD8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsnega\n");

    x = testarmcsnega();
   
    if (x != 0x818283848586878A)
    {
    
        printf("  FAIL! testarmcsnega() success test - expected 0x818283848586878A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcsnegb\n");

    x = testarmcsnegb();
   
    if (x != 0xECEAE8E6DEDCDAD9)
    {
    
        printf("  FAIL! testarmcsnegb() success test - expected 0xECEAE8E6DEDCDAD9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcinca\n");

    x = testarmcinca();
   
    if (x != 0x6)
    {
    
        printf("  FAIL! testarmcinca() success test - expected 0x6, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcincb\n");

    x = testarmcincb();
   
    if (x != 0x5)
    {
    
        printf("  FAIL! testarmcincb() success test - expected 0x5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcinva\n");

    x = testarmcinva();
   
    if (x != 0xFFFFFFFFFFFFFFFA)
    {
    
        printf("  FAIL! testarmcinva() success test - expected 0xFFFFFFFFFFFFFFFA, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcinvb\n");

    x = testarmcinvb();
   
    if (x != 0x5)
    {
    
        printf("  FAIL! testarmcinvb() success test - expected 0x5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcnega\n");

    x = testarmcnega();
   
    if (x != 0xFFFFFFFFFFFFFFFB)
    {
    
        printf("  FAIL! testarmcnega() success test - expected 0xFFFFFFFFFFFFFFFB, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcnegb\n");

    x = testarmcnegb();
   
    if (x != 0x5)
    {
    
        printf("  FAIL! testarmcnegb() success test - expected 0x5, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommaa\n");

    x = testarmldaddcommaa();
   
    if (x != 0x19)
    {
    
        printf("  FAIL! testarmldaddcommaa() success test - expected 0x19, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommab\n");

    x = testarmldaddcommab();
   
    if (x != 0x112233445566231C)
    {
    
        printf("  FAIL! testarmldaddcommab() success test - expected 0x112233445566231C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommac\n");

    x = testarmldaddcommac();
   
    if (x != 0x112233445566271C)
    {
    
        printf("  FAIL! testarmldaddcommac() success test - expected 0x112233445566271C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommad\n");

    x = testarmldaddcommad();
   
    if (x != 0x112233445B6B271C)
    {
    
        printf("  FAIL! testarmldaddcommad() success test - expected 0x112233445B6B271C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommae\n");

    x = testarmldaddcommae();
   
    if (x != 0x1A24344B5B6B271C)
    {
    
        printf("  FAIL! testarmldaddcommae() success test - expected 0x1A24344B5B6B271C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommaf\n");

    x = testarmldaddcommaf();
   
    if (x != 0x1122334455662313)
    {
    
        printf("  FAIL! testarmldaddcommaf() success test - expected 0x1122334455662313, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldaddcommag\n");

    x = testarmldaddcommag();
   
    if (x != 0x1122334455662714)
    {
    
        printf("  FAIL! testarmldaddcommag() success test - expected 0x1122334455662714, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldpcommaa\n");

    x = testarmimmplusplusldpcommaa();
   
    if (x != 0x123456789ABCDEF9)
    {
    
        printf("  FAIL! testarmimmplusplusldpcommaa() success test - expected 0x123456789ABCDEF9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldpcommab\n");

    x = testarmimmplusplusldpcommab();
   
    if (x != 0xF0F0F0F0F0F0F0F8)
    {
    
        printf("  FAIL! testarmimmplusplusldpcommab() success test - expected 0xF0F0F0F0F0F0F0F8, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusldpcommac\n");

    x = testarmimmplusplusldpcommac();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testarmimmplusplusldpcommac() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsimmcommaa\n");

    x = testarmandsimmcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmandsimmcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsimmcommab\n");

    x = testarmandsimmcommab();
   
    if (x != 0x1243)
    {
    
        printf("  FAIL! testarmandsimmcommab() success test - expected 0x1243, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsimmcommac\n");

    x = testarmandsimmcommac();
   
    if (x != 0x100000000ABCDEF0)
    {
    
        printf("  FAIL! testarmandsimmcommac() success test - expected 0x100000000ABCDEF0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmandsimmcommad\n");

    x = testarmandsimmcommad();
   
    if (x != 0x1244)
    {
    
        printf("  FAIL! testarmandsimmcommad() success test - expected 0x1244, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbfccomma\n");

    x = testarmbfccomma();
   
    if (x != 0xFFFFFFFFFFFFFFE3)
    {
    
        printf("  FAIL! testarmbfccomma() success test - expected 0xFFFFFFFFFFFFFFE3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbficomma\n");

    x = testarmbficomma();
   
    if (x != 0xFFFFFFFFFFFFF34F)
    {
    
        printf("  FAIL! testarmbficomma() success test - expected 0xFFFFFFFFFFFFF34F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbfmcomma\n");

    x = testarmbfmcomma();
   
    if (x != 0xFFFFFFFFFFFFFFE3)
    {
    
        printf("  FAIL! testarmbfmcomma() success test - expected 0xFFFFFFFFFFFFFFE3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbfxilcomma\n");

    x = testarmbfxilcomma();
   
    if (x != 0xFFFFFFFFFFFFFDE3)
    {
    
        printf("  FAIL! testarmbfxilcomma() success test - expected 0xFFFFFFFFFFFFFDE3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmmrsregcommaa\n");

    x = testarmmrsregcommaa();
   
    if (x != 0x0000000040000000)
    {
    
        printf("  FAIL! testarmmrsregcommaa() success test - expected 0x0000000040000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmrsregcommab\n");

    x = testarmmrsregcommab();
   
    if (x != 0x0000000000000000)
    {
    
        printf("  FAIL! testarmmrsregcommab() success test - expected 0x0000000000000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmrsregcommac\n");

    x = testarmmrsregcommac();
   
    if (x != 0x00000000A0000000)
    {
    
        printf("  FAIL! testarmmrsregcommac() success test - expected 0x00000000A0000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmsrregcommaa\n");

    x = testarmmsrregcommaa();
   
    if (x != 0x00000000F0000000)
    {
    
        printf("  FAIL! testarmmsrregcommaa() success test - expected 0x00000000F0000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmsrregcommab\n");

    x = testarmmsrregcommab();
   
    if (x != 0x0000000050000000)
    {
    
        printf("  FAIL! testarmmsrregcommab() success test - expected 0x0000000050000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmsrregcommac\n");

    x = testarmmsrregcommac();
   
    if (x != 0x0000000000000000)
    {
    
        printf("  FAIL! testarmmsrregcommac() success test - expected 0x0000000000000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmsrcommaa\n");

    x = testarmmsrcommaa();
   
    if (x != 0x00000000F0000000)
    {
    
        printf("  FAIL! testarmmsrcommaa() success test - expected 0x00000000F0000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmrscommaa\n");

    x = testarmmrscommaa();
   
    if (x != 0x0000000030000000)
    {
    
        printf("  FAIL! testarmmrscommaa() success test - expected 0x0000000030000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaba\n");

    x = testarmccmnimmcommaba();
   
    if (x != 0x0000000060000000)
    {
    
        printf("  FAIL! testarmccmnimmcommaba() success test - expected 0x0000000060000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommabb\n");

    x = testarmccmnimmcommabb();
   
    if (x != 0x0000000090000000)
    {
    
        printf("  FAIL! testarmccmnimmcommabb() success test - expected 0x0000000090000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommabc\n");

    x = testarmccmnimmcommabc();
   
    if (x != 0x0000000090000000)
    {
    
        printf("  FAIL! testarmccmnimmcommabc() success test - expected 0x0000000090000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }


    printf("  testing testarmccmnimmcommaaa\n");

    x = testarmccmnimmcommaaa();
   
    if (x != 0x8765)
    {
    
        printf("  FAIL! testarmccmnimmcommaaa() success test - expected 0x8765, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaab\n");

    x = testarmccmnimmcommaab();
   
    if (x != 0x8766)
    {
    
        printf("  FAIL! testarmccmnimmcommaab() success test - expected 0x8766, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaac\n");

    x = testarmccmnimmcommaac();
   
    if (x != 0x8767)
    {
    
        printf("  FAIL! testarmccmnimmcommaac() success test - expected 0x8767, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaad\n");

    x = testarmccmnimmcommaad();
   
    if (x != 0x8768)
    {
    
        printf("  FAIL! testarmccmnimmcommaad() success test - expected 0x8768, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaae\n");

    x = testarmccmnimmcommaae();
   
    if (x != 0x8769)
    {
    
        printf("  FAIL! testarmccmnimmcommaae() success test - expected 0x8769, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaaf\n");

    x = testarmccmnimmcommaaf();
   
    if (x != 0x876A)
    {
    
        printf("  FAIL! testarmccmnimmcommaaf() success test - expected 0x876A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaag\n");

    x = testarmccmnimmcommaag();
   
    if (x != 0x876B)
    {
    
        printf("  FAIL! testarmccmnimmcommaag() success test - expected 0x876B, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaah\n");

    x = testarmccmnimmcommaah();
   
    if (x != 0x0000000060000000)
    {
    
        printf("  FAIL! testarmccmnimmcommaah() success test - expected 0x0000000060000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaai\n");

    x = testarmccmnimmcommaai();
   
    if (x != 0x0000000060000000)
    {
    
        printf("  FAIL! testarmccmnimmcommaai() success test - expected 0x0000000060000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaaj\n");

    x = testarmccmnimmcommaaj();
   
    if (x != 0x0000000060000000)
    {
    
        printf("  FAIL! testarmccmnimmcommaaj() success test - expected 0x0000000060000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaak\n");

    x = testarmccmnimmcommaak();
   
    if (x != 0x0000000060000000)
    {
    
        printf("  FAIL! testarmccmnimmcommaak() success test - expected 0x0000000060000000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaa\n");

    x = testarmccmnimmcommaa();
   
    if (x != 0x4321)
    {
    
        printf("  FAIL! testarmccmnimmcommaa() success test - expected 0x4321, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommaf\n");

    x = testarmccmnimmcommaf();
   
    if (x != 0x4421)
    {
    
        printf("  FAIL! testarmccmnimmcommaf() success test - expected 0x4421, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommag\n");

    x = testarmccmnimmcommag();
   
    if (x != 0x4521)
    {
    
        printf("  FAIL! testarmccmnimmcommag() success test - expected 0x4521, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommah\n");

    x = testarmccmnimmcommah();
   
    if (x != 0x4621)
    {
    
        printf("  FAIL! testarmccmnimmcommah() success test - expected 0x4621, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommab\n");

    x = testarmccmnimmcommab();
   
    if (x != 0x4322)
    {
    
        printf("  FAIL! testarmccmnimmcommab() success test - expected 0x4322, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommac\n");

    x = testarmccmnimmcommac();
   
    if (x != 0x4323)
    {
    
        printf("  FAIL! testarmccmnimmcommac() success test - expected 0x4323, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommad\n");

    x = testarmccmnimmcommad();
   
    if (x != 0x4324)
    {
    
        printf("  FAIL! testarmccmnimmcommad() success test - expected 0x4324, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnimmcommae\n");

    x = testarmccmnimmcommae();
   
    if (x != 0x4325)
    {
    
        printf("  FAIL! testarmccmnimmcommae() success test - expected 0x4325, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmnregcommaa\n");

    x = testarmccmnregcommaa();
   
    if (x != 0x4326)
    {
    
        printf("  FAIL! testarmccmnregcommaa() success test - expected 0x4326, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmpimmcommaa\n");

    x = testarmccmpimmcommaa();
   
    if (x != 0x4327)
    {
    
        printf("  FAIL! testarmccmpimmcommaa() success test - expected 0x4327, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmpimmcommab\n");

    x = testarmccmpimmcommab();
   
    if (x != 0x4329)
    {
    
        printf("  FAIL! testarmccmpimmcommab() success test - expected 0x4329, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmpregcommaa\n");

    x = testarmccmpregcommaa();
   
    if (x != 0x4328)
    {
    
        printf("  FAIL! testarmccmpregcommaa() success test - expected 0x4328, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmccmpregcommab\n");

    x = testarmccmpregcommab();
   
    if (x != 0x432A)
    {
    
        printf("  FAIL! testarmccmpregcommab() success test - expected 0x432A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcrc32bcommaa\n");

    x = testarmcrc32bcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmcrc32bcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcrc32bcommab\n");

    x = testarmcrc32bcommab();
   
    if (x != 0x0000000077073096) // I did not do the math to make sure this result was the correct one...
    {
    
        printf("  FAIL! testarmcrc32bcommab() success test - expected 0x0000000077073096, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmextrcommaa\n");

    x = testarmextrcommaa();
   
    if (x != 0x3821222324252627) 
    {
    
        printf("  FAIL! testarmextrcommaa() success test - expected 0x3821222324252627, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrmifcommaa\n");

    x = testarmrmifcommaa();
   
    if (x != 0x4329) 
    {
    
        printf("  FAIL! testarmrmifcommaa() success test - expected 0x4329, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrmifcommab\n");

    x = testarmrmifcommab();
   
    if (x != 0x432A) 
    {
    
        printf("  FAIL! testarmrmifcommab() success test - expected 0x432A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrorimmcommaa\n");

    x = testarmrorimmcommaa();
   
    if (x != 0xF0123456789ABCDE)
    {
    
        printf("  FAIL! testarmrorimmcommaa() success test - expected 0xF0123456789ABCDE, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrolimmcommaa\n");

    x = testarmrolimmcommaa();
   
    if (x != 0x3456789ABCDEF012) 
    {
    
        printf("  FAIL! testarmrolimmcommaa() success test - expected 0x3456789ABCDEF012, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrorregcommaa\n");

    x = testarmrorregcommaa();
   
    if (x != 0xDEF0123456789ABC)
    {
    
        printf("  FAIL! testarmrorregcommaa() success test - expected 0xDEF0123456789ABC, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsetf8commaa\n");

    x = testarmsetf8commaa();
   
    if (x != 0x9174)
    {
    
        printf("  FAIL! testarmsetf8commaa() success test - expected 0x9174, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsetf8commab\n");

    x = testarmsetf8commab();
   
    if (x != 0x9176)
    {
    
        printf("  FAIL! testarmsetf8commab() success test - expected 0x9176, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsetf16commaa\n");

    x = testarmsetf16commaa();
   
    if (x != 0x9177)
    {
    
        printf("  FAIL! testarmsetf16commaa() success test - expected 0x9177, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsetf16commab\n");

    x = testarmsetf16commab();
   
    if (x != 0x9178)
    {
    
        printf("  FAIL! testarmsetf16commab() success test - expected 0x9178, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmneglcommaa\n");

    x = testarmsmneglcommaa();
   
    if (x != 0xF)
    {
    
        printf("  FAIL! testarmsmneglcommaa() success test - expected 0xF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbnzcommaa\n");

    x = testarmtbnzcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmtbnzcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbnzcommab\n");

    x = testarmtbnzcommab();
   
    if (x != 0x9981)
    {
    
        printf("  FAIL! testarmtbnzcommab() success test - expected 0x9981, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbnzcommac\n");

    x = testarmtbnzcommac();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmtbnzcommac() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbnzcommad\n");

    x = testarmtbnzcommad();
   
    if (x != 0x9982)
    {
    
        printf("  FAIL! testarmtbnzcommad() success test - expected 0x9982, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbzcommaa\n");

    x = testarmtbzcommaa();
   
    if (x != 0x9983)
    {
    
        printf("  FAIL! testarmtbzcommaa() success test - expected 0x9983, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbzcommab\n");

    x = testarmtbzcommab();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmtbzcommab() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbzcommac\n");

    x = testarmtbzcommac();
   
    if (x != 0x9984)
    {
    
        printf("  FAIL! testarmtbzcommac() success test - expected 0x9984, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmtbzcommad\n");

    x = testarmtbzcommad();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmtbzcommad() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmulcommaa\n");

    x = testarmmulcommaa();
   
    if (x != 0x23)
    {
    
        printf("  FAIL! testarmmulcommaa() success test - expected 0x23, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmvncommaa\n");

    x = testarmmvncommaa();
   
    if (x != 0xFFFFFFFFFFFFFFE0)
    {
    
        printf("  FAIL! testarmmvncommaa() success test - expected 0xFFFFFFFFFFFFFFE0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmvncommab\n");

    x = testarmmvncommab();
   
    if (x != 0xFFFFFFFFFFFFFFC1)
    {
    
        printf("  FAIL! testarmmvncommab() success test - expected 0xFFFFFFFFFFFFFFC1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmvncommac\n");

    x = testarmmvncommac();
   
    if (x != 0x0FFFFFFFFFFFFFFE)
    {
    
        printf("  FAIL! testarmmvncommac() success test - expected 0x0FFFFFFFFFFFFFFE, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegcommaa\n");

    x = testarmnegcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFE1)
    {
    
        printf("  FAIL! testarmnegcommaa() success test - expected 0xFFFFFFFFFFFFFFE1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegcommab\n");

    x = testarmnegcommab();
   
    if (x != 0xFFFFFFFFFFFFFFC2)
    {
    
        printf("  FAIL! testarmnegcommab() success test - expected 0xFFFFFFFFFFFFFFC2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegcommac\n");

    x = testarmnegcommac();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testarmnegcommac() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegscommaa\n");

    x = testarmnegscommaa();
   
    if (x != 0xFFFFFFFFFFFFFFE1)
    {
    
        printf("  FAIL! testarmnegscommaa() success test - expected 0xFFFFFFFFFFFFFFE1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegscommab\n");

    x = testarmnegscommab();
   
    if (x != 0xFFFFFFFFFFFFFFC2)
    {
    
        printf("  FAIL! testarmnegscommab() success test - expected 0xFFFFFFFFFFFFFFC2, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegscommac\n");

    x = testarmnegscommac();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testarmnegscommac() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegscommad\n");

    x = testarmnegscommad();
   
    if (x != 0x7376)
    {
    
        printf("  FAIL! testarmnegscommad() success test - expected 0x7376, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmnegscommae\n");

    x = testarmnegscommae();
   
    if (x != 0x7377)
    {
    
        printf("  FAIL! testarmnegscommae() success test - expected 0x7377, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmovbitmaskimma\n");

    x = testarmmovbitmaskimma();
   
    if (x != 0xC00000000000001F)
    {
    
        printf("  FAIL! testarmmovbitmaskimma() success test - expected 0xC00000000000001F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstpcommaa\n");

    x = testarmstpcommaa();
   
    if (x != 0x4142434445464748)
    {
    
        printf("  FAIL! testarmstpcommaa() success test - expected 0x4142434445464748, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstpcommab\n");

    x = testarmstpcommab();
   
    if (x != 0x5152535455565758)
    {
    
        printf("  FAIL! testarmstpcommab() success test - expected 0x5152535455565758, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstpimmpluspluscommaa\n");

    x = testarmstpimmpluspluscommaa();
   
    if (x != 0x4142434445464749)
    {
    
        printf("  FAIL! testarmstpimmpluspluscommaa() success test - expected 0x4142434445464749, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstpimmpluspluscommab\n");

    x = testarmstpimmpluspluscommab();
   
    if (x != 0x5152535455565759)
    {
    
        printf("  FAIL! testarmstpimmpluspluscommab() success test - expected 0x5152535455565759, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstpimmpluspluscommac\n");

    x = testarmstpimmpluspluscommac();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testarmstpimmpluspluscommac() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstpcommaa\n");

    x = testarmimmplusplusstpcommaa();
   
    if (x != 0x414243444546474A)
    {
    
        printf("  FAIL! testarmimmplusplusstpcommaa() success test - expected 0x414243444546474A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstpcommab\n");

    x = testarmimmplusplusstpcommab();
   
    if (x != 0x515253545556575A)
    {
    
        printf("  FAIL! testarmimmplusplusstpcommab() success test - expected 0x515253545556575A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmimmplusplusstpcommac\n");

    x = testarmimmplusplusstpcommac();
   
    if (x != 0x10)
    {
    
        printf("  FAIL! testarmimmplusplusstpcommac() success test - expected 0x10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldclrcommaa\n");

    x = testarmldclrcommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldclrcommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldclrcommab\n");

    x = testarmldclrcommab();
   
    if (x != 0x4142434445464701)
    {
    
        printf("  FAIL! testarmldclrcommab() success test - expected 0x4142434445464701, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldeorcommaa\n");

    x = testarmldeorcommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldeorcommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldeorcommab\n");

    x = testarmldeorcommab();
   
    if (x != 0x414243444546477D)
    {
    
        printf("  FAIL! testarmldeorcommab() success test - expected 0x414243444546477D, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsetcommaa\n");

    x = testarmldsetcommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldsetcommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsetcommab\n");

    x = testarmldsetcommab();
   
    if (x != 0x414243444546477F)
    {
    
        printf("  FAIL! testarmldsetcommab() success test - expected 0x414243444546477F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmaxcommaa\n");

    x = testarmldsmaxcommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldsmaxcommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmaxcommab\n");

    x = testarmldsmaxcommab();
   
    if (x != 0x4142434445464704)
    {
    
        printf("  FAIL! testarmldsmaxcommab() success test - expected0x4142434445464704, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmaxcommac\n");

    x = testarmldsmaxcommac();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldsmaxcommac() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmaxcommad\n");

    x = testarmldsmaxcommad();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldsmaxcommad() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmincommaa\n");

    x = testarmldsmincommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldsmincommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmincommab\n");

    x = testarmldsmincommab();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldsmincommab() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmincommac\n");

    x = testarmldsmincommac();
   
    if (x != 0x41424344454647FF)
    {
    
        printf("  FAIL! testarmldsmincommac() success test - expected0x41424344454647FF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldsmincommad\n");

    x = testarmldsmincommad();
   
    if (x != 0x4142434445464702)
    {
    
        printf("  FAIL! testarmldsmincommad() success test - expected0x4142434445464702, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumaxcommaa\n");

    x = testarmldumaxcommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldumaxcommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumaxcommab\n");

    x = testarmldumaxcommab();
   
    if (x != 0x4142434445464704)
    {
    
        printf("  FAIL! testarmldumaxcommab() success test - expected0x4142434445464704, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumaxcommac\n");

    x = testarmldumaxcommac();
   
    if (x != 0x41424344454647FF)
    {
    
        printf("  FAIL! testarmldumaxcommac() success test - expected0x41424344454647FF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumaxcommad\n");

    x = testarmldumaxcommad();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldumaxcommad() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumincommaa\n");

    x = testarmldumincommaa();
   
    if (x != 0x03)
    {
    
        printf("  FAIL! testarmldumincommaa() success test - expected 0x03, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumincommab\n");

    x = testarmldumincommab();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldumincommab() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumincommac\n");

    x = testarmldumincommac();
   
    if (x != 0x4142434445464703)
    {
    
        printf("  FAIL! testarmldumincommac() success test - expected0x4142434445464703, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldumincommad\n");

    x = testarmldumincommad();
   
    if (x != 0x4142434445464702)
    {
    
        printf("  FAIL! testarmldumincommad() success test - expected0x4142434445464702, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstaddcommaa\n");

    x = testarmstaddcommaa();
   
    if (x != 0x112233445566231C)
    {
    
        printf("  FAIL! testarmstaddcommaa() success test - expected 0x112233445566231C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmswpcommaa\n");

    x = testarmswpcommaa();
   
    if (x != 0x38)
    {
    
        printf("  FAIL! testarmswpcommaa() success test - expected 0x38, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmswpcommab\n");

    x = testarmswpcommab();
   
    if (x != 0x313233343536371C)
    {
    
        printf("  FAIL! testarmswpcommab() success test - expected 0x313233343536371C, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmldarbcommaa\n");

    x = testarmldarbcommaa();
   
    if (x != 0x3E)
    {
    
        printf("  FAIL! testarmldarbcommaa() success test - expected 0x3E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsxtbcommaa\n");

    x = testarmsxtbcommaa();
   
    if (x != 0x3E)
    {
    
        printf("  FAIL! testarmsxtbcommaa() success test - expected 0x3E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsxtbcommab\n");

    x = testarmsxtbcommab();
   
    if (x != 0xFFFFFFFFFFFFFFDE)
    {
    
        printf("  FAIL! testarmsxtbcommab() success test - expected 0xFFFFFFFFFFFFFFDE, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsxthcommaa\n");

    x = testarmsxthcommaa();
   
    if (x != 0x213E)
    {
    
        printf("  FAIL! testarmsxthcommaa() success test - expected 0x213E, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsxthcommab\n");

    x = testarmsxthcommab();
   
    if (x != 0xFFFFFFFFFFFFDEC1)
    {
    
        printf("  FAIL! testarmsxthcommab() success test - expected 0xFFFFFFFFFFFFDEC1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfxcommaa\n");

    x = testarmsbfxcommaa();
   
    if (x != 0xFFFFFFFFFFFFFFEC)
    {
    
        printf("  FAIL! testarmsbfxcommaa() success test - expected 0xFFFFFFFFFFFFFFEC, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbfizcommaa\n");

    x = testarmsbfizcommaa();
   
    if (x != 0xFFFFFFFFFFFFFC10)
    {
    
        printf("  FAIL! testarmsbfizcommaa() success test - expected 0xFFFFFFFFFFFFFC10, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngccommaa\n");

    x = testarmngccommaa();
   
    if (x != 0xFFFFFFFFFFFFEDCC)
    {
    
        printf("  FAIL! testarmngccommaa() success test - expected 0xFFFFFFFFFFFFEDCC, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngccommab\n");

    x = testarmngccommab();
   
    if (x != 0xFFFFFFFFFFFFEDCB)
    {
    
        printf("  FAIL! testarmngccommab() success test - expected 0xFFFFFFFFFFFFEDCB, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngcscommaa\n");

    x = testarmngcscommaa();
   
    if (x != 0xFFFFFFFFFFFFEDCB)
    {
    
        printf("  FAIL! testarmngcscommaa() success test - expected 0xFFFFFFFFFFFFEDCB, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngcscommab\n");

    x = testarmngcscommab();
   
    if (x != 0xFFFFFFFFFFFFEDCA)
    {
    
        printf("  FAIL! testarmngcscommab() success test - expected 0xFFFFFFFFFFFFEDCA, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngcscommac\n");

    x = testarmngcscommac();
   
    if (x != 0x8010)
    {
    
        printf("  FAIL! testarmngcscommac() success test - expected 0x8010, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmngcscommad\n");

    x = testarmngcscommad();
   
    if (x != 0x8011)
    {
    
        printf("  FAIL! testarmngcscommad() success test - expected 0x8011, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbccommaa\n");

    x = testarmsbccommaa();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmsbccommaa() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbccommab\n");

    x = testarmsbccommab();
   
    if (x != 0x4)
    {
    
        printf("  FAIL! testarmsbccommab() success test - expected 0x4, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbcscommaa\n");

    x = testarmsbcscommaa();
   
    if (x != 0x5)
    {
    
        printf("  FAIL! testarmsbcscommaa() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbcscommab\n");

    x = testarmsbcscommab();
   
    if (x != 0x6)
    {
    
        printf("  FAIL! testarmsbcscommab() success test - expected 0x4, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsbcscommac\n");

    x = testarmsbcscommac();
   
    if (x != 0x8020)
    {
    
        printf("  FAIL! testarmsbcscommac() success test - expected 0x8020, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmsubcommaa\n");

    x = testarmmsubcommaa();
   
    if (x != 0x7)
    {
    
        printf("  FAIL! testarmmsubcommaa() success test - expected 0x7, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmaddlcommaa\n");

    x = testarmsmaddlcommaa();
   
    if (x != 0x5FFC200F1)
    {
    
        printf("  FAIL! testarmsmaddlcommaa() success test - expected 0x5FFC200F1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmsublcommaa\n");

    x = testarmsmsublcommaa();
   
    if (x != 0x1FC003DFF11)
    {
    
        printf("  FAIL! testarmsmsublcommaa() success test - expected 0x1FC003DFF11, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumaddlcommaa\n");

    x = testarmumaddlcommaa();
   
    if (x != 0x5FFC200F1)
    {
    
        printf("  FAIL! testarmumaddlcommaa() success test - expected 0x5FFC200F1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumsublcommaa\n");

    x = testarmumsublcommaa();
   
    if (x != 0x1FC003DFF11)
    {
    
        printf("  FAIL! testarmumsublcommaa() success test - expected 0x1FC003DFF11, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmullcommaa\n");

    x = testarmsmullcommaa();
   
    if (x != 0xF)
    {
    
        printf("  FAIL! testarmsmullcommaa() success test - expected 0xF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmullcommab\n");

    x = testarmsmullcommab();
   
    if (x != 0xFFFFFFFFFFFFFFF1)
    {
    
        printf("  FAIL! testarmsmullcommab() success test - expected 0xFFFFFFFFFFFFFFF1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmulhcommaa\n");

    x = testarmsmulhcommaa();
   
    if (x != 0x0)
    {
    
        printf("  FAIL! testarmsmulhcommaa() success test - expected 0x0, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmulhcommab\n");

    x = testarmsmulhcommab();
   
    if (x != 0xFFFFFFFFFFFFFFFF)
    {
    
        printf("  FAIL! testarmsmulhcommab() success test - expected 0xFFFFFFFFFFFFFFFF, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumullcommaa\n");

    x = testarmumullcommaa();
   
    if (x != 0xFFFFFFF80000000F)
    {
    
        printf("  FAIL! testarmumullcommaa() success test - expected 0xFFFFFFF80000000F, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumullcommab\n");

    x = testarmumullcommab();
   
    if (x != 0x4FFFFFFF1)
    {
    
        printf("  FAIL! testarmumullcommab() success test - expected 0x4FFFFFFF1, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsxtwcommaa\n");

    x = testarmsxtwcommaa();
   
    if (x != 0xFFFFFFFF81234567)
    {
    
        printf("  FAIL! testarmsxtwcommaa() success test - expected 0xFFFFFFFF81234567, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmuxtbcommaa\n");

    x = testarmuxtbcommaa();
   
    if (x != 0x87)
    {
    
        printf("  FAIL! testarmuxtbcommaa() success test - expected 0x87, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmuxthcommaa\n");

    x = testarmuxthcommaa();
   
    if (x != 0x8587)
    {
    
        printf("  FAIL! testarmuxthcommaa() success test - expected 0x8587, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmbrcommaa\n");

    x = testarmbrcommaa();
   
    if (x != 0x0102030405060708)
    {
    
        printf("  FAIL! testarmbrcommaa() success test - expected 0x0102030405060708, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmblrcommaa\n");

    x = testarmblrcommaa();
   
    if (x != 0x3344556611332244)
    {
    
        printf("  FAIL! testarmblrcommaa() success test - expected 0x3344556611332244, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmmnegcommaa\n");

    x = testarmmnegcommaa();
   
    if (x != 0x23)
    {
    
        printf("  FAIL! testarmmnegcommaa() success test - expected 0x23, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmumneglcommaa\n");

    x = testarmumneglcommaa();
   
    if (x != 0xFFFFFFF900000023)
    {
    
        printf("  FAIL! testarmumneglcommaa() success test - expected 0xFFFFFFF900000023, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfizcommaa\n");

    x = testarmubfizcommaa();
   
    if (x != 0x8770000)
    {
    
        printf("  FAIL! testarmubfizcommaa() success test - expected 0x8770000, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmubfxcommaa\n");

    x = testarmubfxcommaa();
   
    if (x != 0x87)
    {
    
        printf("  FAIL! testarmubfxcommaa() success test - expected 0x87, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    if (getrsp() != startingrsp)
    {
        x = startingrsp - getrsp();
        printf("  FAIL! rsp moved - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);
    }

/*
    // FEAT_LSCP
    printf("  testing testarmstlpcommaa\n");

    x = testarmstlpcommaa();
   
    if (x != 0x123456789ABCDEFA)
    {
    
        printf("  FAIL! testarmstlpcommaa() success test - expected 0x123456789ABCDEFA, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmstlpcommab\n");

    x = testarmstlpcommab();
   
    if (x != 0x313233343536373A)
    {
    
        printf("  FAIL! testarmstlpcommab() success test - expected 0x313233343536373A, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/

/*
    // FEAT_THE
    printf("  testing testarmrcwcascommaa\n");

    x = testarmrcwcascommaa();
   
    if (x != 0x1122334455667788) 
    {
    
        printf("  FAIL! testarmrcwcascommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmrcwcascommab\n");

    x = testarmrcwcascommab();
   
    if (x != 0x123456789ABCDEF9) 
    {
    
        printf("  FAIL! testarmrcwcascommab() success test - expected 0x123456789ABCDEF9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/

/*
    // requires FEAT_MOPS
    printf("  testing testarmcpyfpcommaa\n");

    x = testarmcpyfpcommaa();
   
    if (x != 0x1256789A9ABCDEF9)
    {
    
        printf("  FAIL! testarmcpyfpcommaa() success test - expected 0x1256789A9ABCDEF9, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/

/*
    // requires FEAT_LSUI
    printf("  testing testarmcasptcommaa\n");

    x = testarmcasptcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcasptcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspatcommaa\n");

    x = testarmcaspatcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcaspatcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspaltcommaa\n");

    x = testarmcaspaltcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcasplatcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcaspltcommaa\n");

    x = testarmcaspltcommaa();
   
    if (x != 0x1122334455667788)
    {
    
        printf("  FAIL! testarmcaspltcommaa() success test - expected 0x1122334455667788, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/    

/*
    // requires FEAT_CSSC 
    printf("  testing testarmcntcommaa\n");

    x = testarmcntcommaa();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmcntcommaa() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcntcommab\n");

    x = testarmcntcommab();
   
    if (x != 0x4)
    {
    
        printf("  FAIL! testarmcntcommab() success test - expected 0x4, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmaxrega\n");

    x = testarmsmaxrega();
    
    if (x != 0x1)
    {
    
       printf("  FAIL! testarmsmaxrega() success test - expected 0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsmaxregb\n");

    x = testarmsmaxregb();
    
    if (x != 0x0)
    {
    
       printf("  FAIL! testarmsmaxregb() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsminrega\n");

    x = testarmsminrega();
    
    if (x != 0x0)
    {
    
       printf("  FAIL! testarmsminrega() success test - expected 0x0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmsminregb\n");

    x = testarmsminregb();
    
    if (x != -0x1)
    {
    
       printf("  FAIL! testarmsminregb() success test - expected -0x1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/
/*
    // FEAT_CMPBR
    printf("  testing testarmcbimmcommaa\n");

    x = testarmcbimmcommaa();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmcbimmcommaa() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbimmcommab\n");

    x = testarmcbimmcommab();
   
    if (x != 0x1233)
    {
    
        printf("  FAIL! testarmcbimmcommab() success test - expected 0x1233, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbimmcommac\n");

    x = testarmcbimmcommac();
   
    if (x != 0x3)
    {
    
        printf("  FAIL! testarmcbimmcommac() success test - expected 0x3, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbimmcommad\n");

    x = testarmcbimmcommad();
   
    if (x != 0x1234)
    {
    
        printf("  FAIL! testarmcbimmcommad() success test - expected 0x1234, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbimmcommae\n");

    x = testarmcbimmcommae();
   
    if (x != 0x4)
    {
    
        printf("  FAIL! testarmcbimmcommae() success test - expected 0x4, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing testarmcbimmcommaf\n");

    x = testarmcbimmcommaf();
   
    if (x != 0x1235)
    {
    
        printf("  FAIL! testarmcbimmcommaf() success test - expected 0x1235, got 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
        
        return(1);

    }
*/

    return(0);
}

