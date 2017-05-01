#ifndef KTHEMEUX
#define KTHEMEUX
//---------------------------------------------------------------------------
#define THEMEAPI          STDAPI
#define THEMEAPI_(type)   STDAPI_(type)
//---------------------------------------------------------------------------
typedef HANDLE HPAINTBUFFER;  // handle to a buffered paint context
//---------------------------------------------------------------------------
// BP_BUFFERFORMAT
typedef enum _BP_BUFFERFORMAT
{
    BPBF_COMPATIBLEBITMAP,    // Compatible bitmap
    BPBF_DIB,                 // Device-independent bitmap
    BPBF_TOPDOWNDIB,          // Top-down device-independent bitmap
    BPBF_TOPDOWNMONODIB       // Top-down monochrome device-independent bitmap
} BP_BUFFERFORMAT;
//---------------------------------------------------------------------------
// BP_PAINTPARAMS
typedef struct _BP_PAINTPARAMS
{
    DWORD                       cbSize;
    DWORD                       dwFlags; // BPPF_ flags
    const RECT *                prcExclude;
    const BLENDFUNCTION *       pBlendFunction;
} BP_PAINTPARAMS, *PBP_PAINTPARAMS;
//---------------------------------------------------------------------------
#define BPBF_COMPOSITED BPBF_TOPDOWNDIB
//---------------------------------------------------------------------------
THEMEAPI BufferedPaintInit(VOID);
THEMEAPI BufferedPaintUnInit(VOID);
THEMEAPI EndBufferedPaint(HPAINTBUFFER hBufferedPaint, BOOL fUpdateTarget);
THEMEAPI_(HPAINTBUFFER) BeginBufferedPaint(HDC hdcTarget, const RECT* prcTarget, BP_BUFFERFORMAT dwFormat, __in_opt BP_PAINTPARAMS *pPaintParams, __out HDC *phdc);
THEMEAPI BufferedPaintSetAlpha(HPAINTBUFFER hBufferedPaint, __in_opt const RECT *prc, BYTE alpha);
//---------------------------------------------------------------------------
#endif // KTHEMEUX
