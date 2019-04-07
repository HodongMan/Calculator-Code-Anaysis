

#pragma once

#include "CalcError.h"

static constexpr uint32_t BASEXPWR		= 31L;
static constexpr uint32_t BASEX			= 0x80000000; 

typedef uint32_t MANTTYPE;
typedef uint64_t TWO_MANTTYPE;

enum eNUMOBJ_FMT {
	FMT_FLOAT,        
	FMT_SCIENTIFIC,   
	FMT_ENGINEERING   

};

enum eANGLE_TYPE {
	ANGLE_DEG,    
	ANGLE_RAD,    
	ANGLE_GRAD    
};

typedef enum eNUMOBJ_FMT NUMOBJ_FMT;
typedef enum eANGLE_TYPE ANGLE_TYPE;

#pragma warning( push )
#pragma warning( disable:4200 )
typedef struct _number
{
	int32_t sign;        
	int32_t cdigit;    
					   
	int32_t exp;       
					   
	MANTTYPE mant[];

} NUMBER, *PNUMBER, **PPNUMBER;
#pragma warning( pop )

typedef struct _rat
{
	PNUMBER pp;
	PNUMBER pq;
} RAT, *PRAT;

static constexpr uint32_t MAX_LONG_SIZE = 33; 

extern PNUMBER num_one;
extern PNUMBER num_two;
extern PNUMBER num_five;
extern PNUMBER num_six;
extern PNUMBER num_ten;

extern PRAT ln_ten;
extern PRAT ln_two;
extern PRAT rat_zero;
extern PRAT rat_neg_one;
extern PRAT rat_one;
extern PRAT rat_two;
extern PRAT rat_six;
extern PRAT rat_half;
extern PRAT rat_ten;
extern PRAT pt_eight_five;
extern PRAT pi;
extern PRAT pi_over_two;
extern PRAT two_pi;
extern PRAT one_pt_five_pi;
extern PRAT e_to_one_half;
extern PRAT rat_exp;
extern PRAT rad_to_deg;
extern PRAT rad_to_grad;
extern PRAT rat_qword;
extern PRAT rat_dword;
extern PRAT rat_word;
extern PRAT rat_byte;
extern PRAT rat_360;
extern PRAT rat_400;
extern PRAT rat_180;
extern PRAT rat_200;
extern PRAT rat_nRadix;
extern PRAT rat_smallest;
extern PRAT rat_negsmallest;
extern PRAT rat_max_exp;
extern PRAT rat_min_exp;
extern PRAT rat_max_fact;
extern PRAT rat_min_fact;
extern PRAT rat_max_i32;
extern PRAT rat_min_i32;

#define DUPNUM(a,b) destroynum(a);createnum( a, (b)->cdigit );_dupnum(a, b);

#define DUPRAT(a,b) destroyrat(a);createrat(a);DUPNUM((a)->pp,(b)->pp);DUPNUM((a)->pq,(b)->pq);

#define LOGNUMRADIX(pnum) (((pnum)->cdigit+(pnum)->exp)*g_ratio)
#define LOGRATRADIX(prat) (LOGNUMRADIX((prat)->pp)-LOGNUMRADIX((prat)->pq))

#define LOGNUM2(pnum) ((pnum)->cdigit+(pnum)->exp)
#define LOGRAT2(prat) (LOGNUM2((prat)->pp)-LOGNUM2((prat)->pq))

#if defined( DEBUG_RATPAK )

#define createrat(y) (y)=_createrat(); \
{ \
    std::wstringstream outputString; \
    outputString << "createrat " << y << " " << # y << " file= " << __FILE__ << ", line= " << __LINE__ << "\n"; \
    OutputDebugString(outputString.str().c_str()); \
}
#define destroyrat(x) \
{ \
    std::wstringstream outputString; \
    outputString << "destroyrat " << x << " file= " << __FILE__ << ", line= " << __LINE__ << "\n"; \
    OutputDebugString(outputString.str().c_str()); \
} \
_destroyrat(x),(x)=nullptr
#define createnum(y,x) (y)=_createnum(x); \
{ \
    std::wstringstream outputString; \
    outputString << "createnum " << y << " " << # y << " file= " << __FILE__ << ", line= " << __LINE__ << "\n"; \
    OutputDebugString(outputString.str().c_str()); \
}
#define destroynum(x) \
{ \
    std::wstringstream outputString; \
    outputString << "destroynum " << x << " file= " << __FILE__ << ", line= " << __LINE__ << "\n"; \
    OutputDebugString(outputString.str().c_str()); \
} \
_destroynum(x),(x)=nullptr
#else
#define createrat(y) (y)=_createrat()
#define destroyrat(x) _destroyrat(x),(x)=nullptr
#define createnum(y,x) (y)=_createnum(x)
#define destroynum(x) _destroynum(x),(x)=nullptr
#endif

#define RENORMALIZE(x) if ( (x)->pp->exp < 0 ) { \
    (x)->pq->exp -= (x)->pp->exp; \
    (x)->pp->exp = 0; \
    } \
    if ( (x)->pq->exp < 0 ) { \
    (x)->pp->exp -= (x)->pq->exp; \
    (x)->pq->exp = 0; \
    }

#define TRIMNUM(x, precision) if ( !g_ftrueinfinite ) { \
        int32_t trim = (x)->cdigit - precision-g_ratio;\
            if ( trim > 1 ) \
                { \
memmove( (x)->mant, &((x)->mant[trim]), sizeof(MANTTYPE)*((x)->cdigit-trim) ); \
                (x)->cdigit -= trim; \
                (x)->exp += trim; \
                } \
            }

#define TRIMTOP(x, precision) if ( !g_ftrueinfinite ) { \
        int32_t trim = (x)->pp->cdigit - (precision/g_ratio) - 2;\
            if ( trim > 1 ) \
                { \
memmove( (x)->pp->mant, &((x)->pp->mant[trim]), sizeof(MANTTYPE)*((x)->pp->cdigit-trim) ); \
                (x)->pp->cdigit -= trim; \
                (x)->pp->exp += trim; \
                } \
            trim = std::min((x)->pp->exp,(x)->pq->exp);\
            (x)->pp->exp -= trim;\
            (x)->pq->exp -= trim;\
            }

#define SMALL_ENOUGH_RAT(a, precision) (zernum((a)->pp) || ( ( ( (a)->pq->cdigit + (a)->pq->exp ) - ( (a)->pp->cdigit + (a)->pp->exp ) - 1 ) * g_ratio > precision ) )

#define CREATETAYLOR() PRAT xx=nullptr;\
    PNUMBER n2=nullptr; \
    PRAT pret=nullptr; \
    PRAT thisterm=nullptr; \
    DUPRAT(xx,*px); \
    mulrat(&xx,*px, precision); \
    createrat(pret); \
    pret->pp=i32tonum( 0L, BASEX ); \
    pret->pq=i32tonum( 0L, BASEX );

#define DESTROYTAYLOR() destroynum( n2 ); \
    destroyrat( xx );\
    destroyrat( thisterm );\
    destroyrat( *px );\
    trimit(&pret, precision);\
    *px=pret;

#define INC(a) if ( (a)->mant[0] < BASEX - 1 ) \
    { \
    (a)->mant[0]++; \
    } \
    else \
    { \
    addnum( &(a), num_one, BASEX); \
    }

#define MSD(x) ((x)->mant[(x)->cdigit-1])
#define MULNUM(b) mulnumx( &(thisterm->pp), b);

#define DIVNUM(b) mulnumx( &(thisterm->pq), b);

#define NEXTTERM(p,d,precision) mulrat(&thisterm,p,precision);d addrat( &pret, thisterm, precision )

extern bool g_ftrueinfinite; 

extern int32_t g_ratio;
extern void SetDecimalSeparator( wchar_t decimalSeparator );

extern void ChangeConstants( uint32_t radix, int32_t precision );

extern bool equnum(_In_ PNUMBER a, _In_ PNUMBER b);     // returns true of a == b
extern bool lessnum(_In_ PNUMBER a, _In_ PNUMBER b);    // returns true of a < b
extern bool zernum(_In_ PNUMBER a);                // returns true of a == 0
extern bool zerrat(_In_ PRAT a);                   // returns true if a == 0/q
extern std::wstring NumberToString(_Inout_ PNUMBER& pnum, int format, uint32_t radix, int32_t precision);

// returns a text representation of a PRAT
extern std::wstring RatToString(_Inout_ PRAT& prat, int format, uint32_t radix, int32_t precision);
// converts a PRAT into a PNUMBER
extern PNUMBER RatToNumber(_In_ PRAT prat, uint32_t radix, int32_t precision);
// flattens a PRAT by converting it to a PNUMBER and back to a PRAT
extern void flatrat(_Inout_ PRAT& prat, uint32_t radix, int32_t precision);

extern int32_t numtoi32(_In_ PNUMBER pnum, uint32_t radix);
extern int32_t rattoi32(_In_ PRAT prat, uint32_t radix, int32_t precision);
uint64_t rattoUi64(_In_ PRAT prat, uint32_t radix, int32_t precision);
extern PNUMBER _createnum(_In_ uint32_t size); // returns an empty number structure with size digits
extern PNUMBER nRadixxtonum(_In_ PNUMBER a, uint32_t radix, int32_t precision);
extern PNUMBER gcd(_In_ PNUMBER a, _In_ PNUMBER b);
extern PNUMBER StringToNumber(std::wstring_view numberString, uint32_t radix, int32_t precision); // takes a text representation of a number and returns a number.

																								  // takes a text representation of a number as a mantissa with sign and an exponent with sign.
extern PRAT StringToRat(bool mantissaIsNegative, std::wstring_view mantissa, bool exponentIsNegative, std::wstring_view exponent, uint32_t radix, int32_t precision);

extern PNUMBER i32factnum(int32_t ini32, uint32_t radix);
extern PNUMBER i32prodnum(int32_t start, int32_t stop, uint32_t radix);
extern PNUMBER i32tonum(int32_t ini32, uint32_t radix);
extern PNUMBER Ui32tonum(uint32_t ini32, uint32_t radix);
extern PNUMBER numtonRadixx(PNUMBER a, uint32_t radix);

// creates a empty/undefined rational representation (p/q)
extern PRAT _createrat(void);

// returns a new rat structure with the acos of x->p/x->q taking into account
// angle type
extern void acosanglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

// returns a new rat structure with the acosh of x->p/x->q
extern void acoshrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the acos of x->p/x->q
extern void acosrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the asin of x->p/x->q taking into account
// angle type
extern void asinanglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

extern void asinhrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);
// returns a new rat structure with the asinh of x->p/x->q

// returns a new rat structure with the asin of x->p/x->q
extern void asinrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the atan of x->p/x->q taking into account
// angle type
extern void atananglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

// returns a new rat structure with the atanh of x->p/x->q
extern void atanhrat(_Inout_ PRAT *px, int32_t precision);

// returns a new rat structure with the atan of x->p/x->q
extern void atanrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the cosh of x->p/x->q
extern void coshrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the cos of x->p/x->q
extern void cosrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the cos of x->p/x->q taking into account
// angle type
extern void cosanglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

// returns a new rat structure with the exp of x->p/x->q this should not be called explicitly.
extern void _exprat(_Inout_ PRAT *px, int32_t precision);

// returns a new rat structure with the exp of x->p/x->q
extern void exprat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the log base 10 of x->p/x->q
extern void log10rat(_Inout_ PRAT *px, int32_t precision);

// returns a new rat structure with the natural log of x->p/x->q
extern void lograt(_Inout_ PRAT *px, int32_t precision);

extern PRAT i32torat(int32_t ini32);
extern PRAT Ui32torat(uint32_t inui32);
extern PRAT numtorat(_In_ PNUMBER pin, uint32_t radix);

extern void sinhrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);
extern void sinrat(_Inout_ PRAT *px);

// returns a new rat structure with the sin of x->p/x->q taking into account
// angle type
extern void sinanglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

extern void tanhrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);
extern void tanrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);

// returns a new rat structure with the tan of x->p/x->q taking into account
// angle type
extern void tananglerat(_Inout_ PRAT *px, ANGLE_TYPE angletype, uint32_t radix, int32_t precision);

extern void _dupnum(_In_ PNUMBER dest, _In_ const NUMBER * const src);

extern void _destroynum(_In_ PNUMBER pnum);
extern void _destroyrat(_In_ PRAT prat);
extern void addnum(_Inout_ PNUMBER *pa, _In_ PNUMBER b, uint32_t radix);
extern void addrat(_Inout_ PRAT *pa, _In_ PRAT b, int32_t precision);
extern void andrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void divnum(_Inout_ PNUMBER *pa, _In_ PNUMBER b, uint32_t radix, int32_t precision);
extern void divnumx(_Inout_ PNUMBER *pa, _In_ PNUMBER b, int32_t precision);
extern void divrat(_Inout_ PRAT *pa, _In_ PRAT b, int32_t precision);
extern void fracrat(_Inout_ PRAT *pa, uint32_t radix, int32_t precision);
extern void factrat(_Inout_ PRAT *pa, uint32_t radix, int32_t precision);
extern void modrat(_Inout_ PRAT *pa, _In_ PRAT b);
extern void gcdrat(_Inout_ PRAT *pa, int32_t precision);
extern void intrat(_Inout_ PRAT *px, uint32_t radix, int32_t precision);
extern void mulnum(_Inout_ PNUMBER *pa, _In_ PNUMBER b, uint32_t radix);
extern void mulnumx(_Inout_ PNUMBER *pa, _In_ PNUMBER b);
extern void mulrat(_Inout_ PRAT *pa, _In_ PRAT b, int32_t precision);
extern void numpowi32(_Inout_ PNUMBER *proot, int32_t power, uint32_t radix, int32_t precision);
extern void numpowi32x(_Inout_ PNUMBER *proot, int32_t power);
extern void orrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void powrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void powratNumeratorDenominator(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void powratcomp(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void ratpowi32(_Inout_ PRAT *proot, int32_t power, int32_t precision);
extern void remnum(_Inout_ PNUMBER *pa, _In_ PNUMBER b, uint32_t radix);
extern void rootrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void scale2pi(_Inout_ PRAT *px, uint32_t radix, int32_t precision);
extern void scale(_Inout_ PRAT *px, _In_ PRAT scalefact, uint32_t radix, int32_t precision);
extern void subrat(_Inout_ PRAT *pa, _In_ PRAT b, int32_t precision);
extern void xorrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void lshrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern void rshrat(_Inout_ PRAT *pa, _In_ PRAT b, uint32_t radix, int32_t precision);
extern bool rat_equ(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern bool rat_neq(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern bool rat_gt(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern bool rat_ge(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern bool rat_lt(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern bool rat_le(_In_ PRAT a, _In_ PRAT b, int32_t precision);
extern void inbetween(_In_ PRAT *px, _In_ PRAT range, int32_t precision);
extern void trimit(_Inout_ PRAT *px, int32_t precision);
extern void _dumprawrat(_In_ const wchar_t *varname, _In_ PRAT rat, std::wostream& out);
extern void _dumprawnum(_In_ const wchar_t *varname, _In_ PNUMBER num, std::wostream& out);