
// lab1View.h : interface of the Clab1View class
//

#pragma once


class Clab1View : public CView
{
protected: // create from serialization only
	Clab1View() noexcept;
	DECLARE_DYNCREATE(Clab1View)

// Attributes
public:
	Clab1Doc* GetDocument() const;

// Operations
public:
	void SetTransform(CDC* pDC, float cx, float cy, float rx, float ry, float alfa, float beta, XFORM* oldXForm);
	void DrawClock(CDC* pDC, CBrush* oldBrush, CBrush* newBrushBrown, CBrush* newBrushBlack, CPen* newPenBrown, CString WMFName, HENHMETAFILE MF, ENHMETAHEADER emfHeader, float beta, float lokacijaX, float lokacijaY);
	void SetBitmapTransform(CDC* pDC, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM* oldXForm);
	COLORREF SetBitmapRGBFilter(CBitmap*bmp, bool r, bool g, bool b);
	void DrawBitmap(CDC* pDC, int x, int y, float scale, float alpha, CString name);
	void DrawTransparentBitmap(CDC* pDC, int x, int y, float scale, bool r, bool g, bool b, CString name);
	void DrawPuzzlePart(CDC* pDC, int x, int y, int cx, int cy, float scale, float angle, bool mirror, bool r, bool g, bool b, CString name);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Clab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in lab1View.cpp
inline Clab1Doc* Clab1View::GetDocument() const
   { return reinterpret_cast<Clab1Doc*>(m_pDocument); }
#endif

