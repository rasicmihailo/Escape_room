
// lab1View.cpp : implementation of the Clab1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab1.h"
#endif

#include "lab1Doc.h"
#include "lab1View.h"
#include "DImage.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab1View

IMPLEMENT_DYNCREATE(Clab1View, CView)

BEGIN_MESSAGE_MAP(Clab1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



	bool m_bHitCabinet; //ormar
	bool m_bHitDoor; //vrata
	bool m_bHitKey; //kljuc
	bool m_bHitCurtain; //zavesa   //

	bool m_bHitDrawer;  //fioka
	bool m_bHitKey2; //kljuc iz fioke

	int m_bHitClockwiseBig; //velika kazaljka
	int m_bHitClockwiseSmall; //mala kazaljka
	int m_bHitPendulum; //klatno

	int m_bHitClock;  //okretanje sata

	bool m_bHitR; //crveni filter
	bool m_bHitG; //zeleni filter
	bool m_bHitB; //plavi filter

	int m_bHitPicture; //okretanje slike

// Clab1View construction/destruction

Clab1View::Clab1View() noexcept
{
	// TODO: add construction code here

	m_bHitCabinet = false;

	m_bHitDoor = false;

	m_bHitKey = false;

	m_bHitCurtain = false; //

	m_bHitDrawer = false;

	m_bHitKey2 = false;

	m_bHitClockwiseBig = 0;

	m_bHitClockwiseSmall = 0;

	m_bHitPendulum = 1; //centralna pozicija klatna = 1, levo = 0, desno = 2, centralna pozicija u drugom prolazu = 4

	m_bHitClock = 0;

	m_bHitR = false;

	m_bHitG = false;

	m_bHitB = false;

	m_bHitPicture = 0;
}

Clab1View::~Clab1View()
{
}

BOOL Clab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


// Clab1View drawing

void Clab1View::OnDraw(CDC* pDC)
{
	Clab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	//ceo koncept SelectObject!!!
	/*
	CPen* newPen = new CPen(PS_SOLID, 0, RGB(0, 0, 255));
	CPen* oldPen = pDC->SelectObject(newPen); //vraca objekat koji se koristio pre
	pDC->MoveTo(10, 10);
	pDC->LineTo(300, 300);
	pDC->SelectObject(oldPen);
	newPen->DeleteObject();
	*/


	CRect rect;
	GetClientRect(&rect);
	pDC = GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(800, 800);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetViewportOrg(0, 0); //podrazumevano

	CPen* newPenBrown = new CPen(PS_SOLID, 2, RGB(102, 51, 0));
	CPen* oldPen = pDC->SelectObject(newPenBrown); //vraca objekat koji se koristio pre

	//COLORREF oldBkColor; //crna boja za pozadinu

#pragma region Zadnji zid:

	CBrush newBrushWall1(RGB(255, 192, 128));
	CBrush* oldBrush = pDC->SelectObject(&newBrushWall1);

	pDC->Rectangle(80, 80, 720, 720); //zadnji zid

	pDC->SelectObject(oldBrush);
	newBrushWall1.DeleteObject();

#pragma endregion

#pragma region Bocni zidovi:

	CBrush newBrushWall2(RGB(198, 140, 83));
	oldBrush = pDC->SelectObject(&newBrushWall2);

	CPoint pointsLeft[] = { CPoint(0, 0), CPoint(0, 800), CPoint(80, 720), CPoint(80, 80) };
	pDC->Polygon(pointsLeft, 4); //levi bocni zid

	CPoint pointsRight[] = { CPoint(800, 0), CPoint(800, 800), CPoint(720, 720), CPoint(720, 80) };
	pDC->Polygon(pointsRight, 4); //desni bocni zid

	pDC->SelectObject(oldBrush);
	newBrushWall2.DeleteObject();

#pragma endregion

#pragma region Inventar:

	CBrush newBrushGray(RGB(179, 179, 179));
	oldBrush = pDC->SelectObject(&newBrushGray);

	pDC->RoundRect(10, 10, 85, 70, 10, 10); //inventar

	pDC->SelectObject(oldBrush);
	newBrushGray.DeleteObject();

#pragma endregion

#pragma region Pod:

	CBrush newBrushFloor (RGB(194, 194, 163));
	oldBrush = pDC->SelectObject(&newBrushFloor);

	CPoint pointsBottom[] = { CPoint(0, 800), CPoint(800, 800), CPoint(720, 720), CPoint(80, 720) };
	pDC->Polygon(pointsBottom, 4); //pod

	pDC->SelectObject(oldBrush);
	newBrushFloor.DeleteObject();

#pragma endregion

#pragma region Prozor:

	CBrush* newBrushBrown = new CBrush(RGB(153, 102, 51)); //necemo da je brisemo na kraju jer cemo jos da je koristimo
	oldBrush = pDC->SelectObject(newBrushBrown);

	pDC->Rectangle(300, 180, 500, 530); //okvir prozora

	CBrush newBrushBlue(RGB(0, 204, 255));
	pDC->SelectObject(&newBrushBlue); //ne upisujemo u oldBrush povratnu vrednost jer bo to bila braon boja!!!

	pDC->Rectangle(310, 190, 490, 520); //celo staklo  //
	//pDC->Rectangle(405, 190, 490, 520); //desno staklo ne postoji vise   //

	CString WMFName = CString("Michael.emf");  //
	HENHMETAFILE MF;  //
	ENHMETAHEADER emfHeader;  //
	MF = GetEnhMetaFile(WMFName); //
	GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader); //
	PlayEnhMetaFile(pDC->m_hDC, MF, CRect(310, 190, 490, 543)); //
	DeleteEnhMetaFile(MF); //

	pDC->SelectObject(newBrushBrown); //

	pDC->BeginPath(); //
		pDC->MoveTo(395, 190); //
		pDC->LineTo(405, 190); //
		pDC->LineTo(405, 520); //
		pDC->LineTo(395, 520); //
	pDC->EndPath(); //
	pDC->StrokeAndFillPath(); //daska koja deli stakla   //

	pDC->BeginPath(); //
		pDC->MoveTo(396, 188); //
		pDC->LineTo(404, 188); //
		pDC->LineTo(404, 522); //
		pDC->LineTo(396, 522); //
	pDC->EndPath();  //
	pDC->FillPath();  //da ne bi ostale linije ispod i iznad daske koja deli stakla   //

	pDC->SelectObject(oldBrush);
	newBrushBlue.DeleteObject();

#pragma endregion

#pragma region Zavesa:

	CBrush newBrushYellow(RGB(255, 255, 153));
	oldBrush = pDC->SelectObject(&newBrushYellow);

	if (m_bHitCurtain) { //zavesa otvorena, kliknuto na nju  //
		CPoint pointsBezier[] = { CPoint(495, 530), CPoint(485, 450), CPoint(480, 490) };  //

		pDC->BeginPath();   //
			pDC->MoveTo(480, 140); //
			pDC->LineTo(505, 140); //
			pDC->LineTo(505, 490); //
			pDC->PolyBezierTo(pointsBezier, 3); //
			pDC->LineTo(480, 140); //
		pDC->EndPath(); //

		pDC->StrokeAndFillPath(); //zavesa pomerena  //

	}  //
	else { //zavesa zatvorena, inicijalno   //

		CPoint pointsBezier[] = { CPoint(460, 530), CPoint(340, 450), CPoint(295, 490) };

		pDC->BeginPath();
			pDC->MoveTo(295, 140);
			pDC->LineTo(505, 140);
			pDC->LineTo(505, 490);
			pDC->PolyBezierTo(pointsBezier, 3);
			pDC->LineTo(295, 140);
		pDC->EndPath();

		pDC->StrokeAndFillPath(); //zavesa
	}   //

	pDC->SelectObject(oldBrush);
	newBrushYellow.DeleteObject();

#pragma endregion

#pragma region Garnisla:

	oldBrush = pDC->SelectObject(newBrushBrown); //vec postoji braon brush

	pDC->RoundRect(280, 120, 520, 160, 40, 40); //garnisla

	pDC->SelectObject(oldBrush);

#pragma endregion

#pragma region Plakar:

	oldBrush = pDC->SelectObject(newBrushBrown); //vec postoji braon brush

	pDC->Rectangle(40, 160, 160, 760); //prednji deo

	CPoint pointsCabinet[] = { CPoint(160, 160), CPoint(200, 200), CPoint(200, 720), CPoint(160, 760) };
	pDC->Polygon(pointsCabinet, 4); //stranica

	pDC->Rectangle(50, 570, 150, 650); //gornja fijoka
	

	pDC->Rectangle(100, 175, 150, 555); //desno krilo


	CBrush newBrushOrange(RGB(255, 153, 0)); //necemo da je brisemo na kraju jer cemo jos da je koristimo
	pDC->SelectObject(&newBrushOrange); //ne upisujemo u oldBrush povratnu vrednost jer bo to bila braon boja!!!

	pDC->Ellipse(95, 605, 105, 615); //rucica gornja fijoka
	

	pDC->Ellipse(105, 365, 115, 375); //rucica desno krilo
	
	CBrush* newBrushBlack = new CBrush(RGB(0, 0, 0)); //necemo da je brisemo na kraju jer cemo jos da je koristimo

	if (m_bHitCabinet){ //kliknuto na rucicu
		
		pDC->SelectObject(newBrushBrown); //vec postoji braon brush

		CPoint pointsCabinetOpen[] = { CPoint(10, 160), CPoint(50, 175), CPoint(50, 555), CPoint(10, 570) };
		pDC->Polygon(pointsCabinetOpen, 4); //levo krilo otvoreno


		pDC->SelectObject(newBrushBlack);
		pDC->Rectangle(50, 175, 100, 555); //unutrasnjost ormara;


		if (m_bHitKey) { //kliknuto na kljuc

			CString WMFName = CString("Key.emf");
			HENHMETAFILE MF;
			ENHMETAHEADER emfHeader;
			MF = GetEnhMetaFile(WMFName);
			GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
			PlayEnhMetaFile(pDC->m_hDC, MF, CRect(15, 25, 40, 55));
			DeleteEnhMetaFile(MF);
			
			

		}
		else { //nije jos uvek kliknuto na kljuc

			CString WMFName = CString("Key.emf");
			HENHMETAFILE MF;
			ENHMETAHEADER emfHeader;
			MF = GetEnhMetaFile(WMFName);
			GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
			PlayEnhMetaFile(pDC->m_hDC, MF, CRect(55, 515, 80, 545));
			DeleteEnhMetaFile(MF);

		}




	}
	else { //prvi prolaz, inicijalno

		pDC->SelectObject(newBrushBrown); //vec postoji braon brush
		//oldBkColor = pDC->SetBkColor(RGB(0, 0, 0)); //boja unutrasnjosti plakara
		pDC->Rectangle(50, 175, 100, 555); //levo krilo
		//pDC->SetBkColor(oldBkColor);


		
		pDC->SelectObject(&newBrushOrange); //ne upisujemo u oldBrush povratnu vrednost jer bo to bila braon boja!!!
		pDC->Ellipse(85, 365, 95, 375); //rucica levo krilo
	}



	/// lab1 vezba na casu ///////////////////////////////////////////

	if (m_bHitDrawer && m_bHitKey) { //fioka otvorena

		pDC->SelectObject(newBrushBlack);

		CPoint pointsDrawerOpenIn[] = { CPoint(50, 665), CPoint(150, 665), CPoint(110, 705), CPoint(10, 705) };
		pDC->Polygon(pointsDrawerOpenIn, 4); //unutrasnjost fioke

		pDC->SelectObject(newBrushBrown);
		

		CPoint pointsDrawerOpen[] = { CPoint(110, 705), CPoint(150, 665), CPoint(150, 745), CPoint(110, 790) };
		pDC->Polygon(pointsDrawerOpen, 4); //desna ivica fioke



		if (m_bHitKey2) { //kliknuto na kljuc 2

			CString WMFName = CString("Key.emf");
			HENHMETAFILE MF;
			ENHMETAHEADER emfHeader;
			MF = GetEnhMetaFile(WMFName);
			GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
			PlayEnhMetaFile(pDC->m_hDC, MF, CRect(50, 25, 75, 55));
			DeleteEnhMetaFile(MF);

		}
		else { //nije jos uvek kliknuto na kljuc 2, inicijalno

			CString WMFName = CString("Key.emf");
			HENHMETAFILE MF;
			ENHMETAHEADER emfHeader;
			MF = GetEnhMetaFile(WMFName);
			GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
			PlayEnhMetaFile(pDC->m_hDC, MF, CRect(70, 675, 95, 705));
			DeleteEnhMetaFile(MF);

		}
		pDC->Rectangle(10, 705, 110, 790); //donja fioka  //ceoni deo

		pDC->SelectObject(&newBrushOrange);
		pDC->Ellipse(55, 744, 65, 756); //rucica donja fioka

	}
	else { //fioka zatvorena inicijalno

		pDC->SelectObject(newBrushBrown);
		pDC->Rectangle(50, 665, 150, 745); //donja fioka

		pDC->SelectObject(&newBrushOrange);
		pDC->Ellipse(95, 700, 105, 710); //rucica donja fioka

	}
	
	//////////////////////////////////////////// lab1 vezba na casu //

	pDC->SelectObject(oldBrush);

#pragma endregion

	// lab2 ////////////////////////////////////////////////////

	float beta = m_bHitClock*30; //ugao za koji se rotira ceo sat u stepenima - m_bHitClock ide od 0 do 12
	float lokacijaX = 610.0; //lokacija centra sata - x osa
	float lokacijaY = 520.0; //lokacija centra sata - y osa
	DrawClock(pDC, oldBrush, newBrushBrown, newBrushBlack, newPenBrown, WMFName, MF, emfHeader, beta, lokacijaX, lokacijaY);

	////////////////////////////////////////////////// lab2 //


	// lab3 ////////////////////////////////////////////////////

	float gama = m_bHitPicture * 30; //ugao za koji se rotira slika

	CString picture;
	picture = "Ram.bmp";
	DrawBitmap(pDC, 610, 300, 0.4, gama, picture); //610, 300 centar slike

	picture = "Part1.bmp";
	//DrawPuzzlePart(pDC, 585, 248, 0, 0, 0.4, 0.0 + gama, false, true, false, false, picture); //-25, -52
	DrawPuzzlePart(pDC, 610, 300, -63, -127, 0.4, 0.0 + gama, false, true, false, false, picture);

	picture = "Part2.bmp";
	//DrawPuzzlePart(pDC, 640, 253, 0, 0, 0.4, 326.0 + gama, false, false, true, false, picture); //+40, - 47
	DrawPuzzlePart(pDC, 610, 300, 120, -57, 0.4, 326.0 + gama, false, false, true, false, picture);

	picture = "Part3.bmp";
	//DrawPuzzlePart(pDC, 577, 342, 0, 0, 0.4, 116.0 + gama, false, false, false, true, picture); //-33, +42
	DrawPuzzlePart(pDC, 610, 300, 134, 28, 0.4, 116.0 + gama, false, false, false, true, picture);

	picture = "Part4.bmp";
	//DrawPuzzlePart(pDC, 637, 347, 0, 0, 0.4, 301.0 + gama, true, m_bHitR, m_bHitG, m_bHitB, picture); //+27, +47
	DrawPuzzlePart(pDC, 610, 300, 68, 115, 0.4, 301.0 + gama, true, m_bHitR, m_bHitG, m_bHitB, picture);

	//////////////////////////////////////////////////// lab3 //

#pragma region Vrata:

	if (m_bHitDoor) { //kliknuto na vrata

		oldBrush = pDC->SelectObject(newBrushBlack); //vec postoji crni brush

		CPoint pointsDoor[] = { CPoint(730, 160), CPoint(790, 110), CPoint(790, 790), CPoint(730, 730) };
		//oldBkColor = pDC->SetBkColor(RGB(0, 0, 0)); //boja spoljasnjosti kada se otvore vrata
		pDC->Polygon(pointsDoor, 4); //prostor iza otvorenih vrata, napolje
		//pDC->SetBkColor(oldBkColor);

		pDC->SelectObject(newBrushBrown);
		pDC->Rectangle(645, 160, 730, 730); //spoljasnji deo vrata

	}
	else { //vrata zatvorena, inicijalno

		oldBrush = pDC->SelectObject(newBrushBrown); //vec postoji braon brush

		CPoint pointsDoor[] = { CPoint(730, 160), CPoint(790, 110), CPoint(790, 790), CPoint(730, 730) };
		//oldBkColor = pDC->SetBkColor(RGB(0, 0, 0)); //boja spoljasnjosti kada se otvore vrata
		pDC->Polygon(pointsDoor, 4); //vrata
		//pDC->SetBkColor(oldBkColor);


		pDC->SelectObject(&newBrushOrange);  //vec postoji narandzasta brush
		pDC->Ellipse(773, 460, 783, 474); //rucica za kvaku
		pDC->Ellipse(756, 455, 779, 479); //kvaka

		pDC->SelectObject(newBrushBlack); //vec postoji crni brush

		pDC->Ellipse(778, 485, 783, 500); //klucaonica

	}

	pDC->SelectObject(oldBrush);
	newBrushOrange.DeleteObject(); //vise nam ne treba narandzasta

#pragma endregion   //vrata moraju da se crtaju posle sata i posle slike jer ih malo preklapaju


}


void Clab1View::DrawClock(CDC* pDC, CBrush* oldBrush, CBrush* newBrushBrown, CBrush* newBrushBlack, CPen* newPenBrown, CString WMFName, HENHMETAFILE MF, ENHMETAHEADER emfHeader, float beta, float lokacijaX, float lokacijaY) {
	
	// lab2 //////////////////////////////////////////////////////////////////

#pragma region Sat-kutija za klatno-klatno:

	XFORM oldXForm;
	int prevMode;
	BOOL b;

	CBrush newBrushYellowClock = RGB(255, 204, 51); //boja za sat




	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, 0.0, beta, &oldXForm); //610, 190 - centar sata


	oldBrush = pDC->SelectObject(newBrushBrown); //vec postoji braon boja
	pDC->RoundRect(-50, 10, 50, 210, 20, 20); //kutija za klatno, okvir

	pDC->SelectObject(newBrushBlack);
	pDC->RoundRect(-42, 18, 42, 202, 20, 20); //kutija za klatno, unutrasnjost



	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);




	float deg;

	if (m_bHitPendulum == 0)  //skaliranje u pozicija klatna u stepene
		deg = 9.0;
	else if (m_bHitPendulum == 1)
		deg = 0.0;
	else if (m_bHitPendulum == 2)
		deg = 351.0;
	else if (m_bHitPendulum == 3)
		deg = 0.0;

	pDC->SelectObject(&newBrushYellowClock);
	pDC->SelectObject(newPenBrown);

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, deg, beta, &oldXForm); //610, 190 - centar sata

	pDC->Rectangle(-3, 0, 3, 170); //klatno drska
	pDC->Ellipse(-14, 156, 14, 184); //klatno kugla

	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	pDC->SelectObject(oldBrush);



	CFont fontGraphic;
	fontGraphic.CreateFontW(18, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)"Arial");
	CFont* oldFont = pDC->SelectObject(&fontGraphic);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(153, 102, 51));
	CString graphic("GRAFIKA");

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, deg + 270, beta, &oldXForm); //610, 190 - centar sata
	//deg + 270 da bi bilo ispisano uspravno, to je ustvari -90 stepeni

	pDC->TextOutW(-156, -18, graphic); //text "grafika" pored klatna

	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	pDC->SelectObject(oldFont);
	fontGraphic.DeleteObject();

#pragma endregion

#pragma region Sat-fiksni delovi:

	//za delove sata koji su mogli i bez transformacije (okvir, kutija za klatno...)
	//se dodaje beta ugao kao poseban parametar u PrimeniTransformaciju() za koji se pomera ceo sat
	//dok se kod delova kao sto su, kazaljke, podeoci, brojevi sabira sa oglom za koji treba da se rotiraju

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, 0.0, beta, &oldXForm); //610, 190 - centar sata


	oldBrush = pDC->SelectObject(newBrushBrown);
	pDC->Ellipse(-70, -70, 70, 70); //okvir sata

	pDC->SelectObject(&newBrushYellowClock);
	pDC->Ellipse(-60, -60, 60, 60); //pozadina sata

	CPen newPenBlack1(PS_SOLID, 1, RGB(0, 0, 0));
	CPen newPenBlack2(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&newPenBlack1);
	CBrush newBrushWhite = RGB(255, 255, 255);
	pDC->SelectObject(&newBrushWhite);
	pDC->Ellipse(-40, -40, 40, 40); //spoljasnji okvir podeoka
	pDC->Ellipse(-32, -30, 32, 32); //unutrasnji okvir podeoka


	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);



	CFont fontNumber;
	fontNumber.CreateFontW(16, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (LPCTSTR)"Arial");
	oldFont = pDC->SelectObject(&fontNumber);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));

	CString number;

	CBrush newBrushYellowClock2(RGB(255, 255, 102));

	for (float i = 0.0; i < 360.0; i = i + 30.0) {
		prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
		SetTransform(pDC, lokacijaX, lokacijaY, 0.0, -50.0, i + beta, 360.0 - i, &oldXForm); //610, 190 - centar sata
		//360-i zato da se ne bi sve brojke bile uspravno

		pDC->SelectObject(&newBrushYellowClock2);

		pDC->BeginPath();
		pDC->Ellipse(-7, -7, 8, 8); //krugovi oko brojeva
		pDC->EndPath();
		pDC->FillPath();

		if ((int)i == 0) {
			number = "12";
			pDC->TextOutW(-5, -5, number); //rimski brojevi na casovniku: 12
		}
		else if ((int)i == 30) {
			number = "1";
			pDC->TextOutW(-1, -7, number); //rimski brojevi na casovniku: 1
		}
		else if ((int)i == 60) {
			number = "2";
			pDC->TextOutW(-2, -7, number); //rimski brojevi na casovniku: 2
		}
		else if ((int)i == 90) {
			number = "3";
			pDC->TextOutW(-2, -7, number); //rimski brojevi na casovniku: 3
		}
		else if ((int)i == 120) {
			number = "4";
			pDC->TextOutW(-4, -7, number); //rimski brojevi na casovniku: 4
		}
		else if ((int)i == 150) {
			number = "5";
			pDC->TextOutW(-3, -7, number); //rimski brojevi na casovniku: 5
		}
		else if ((int)i == 180) {
			number = "6";
			pDC->TextOutW(-4, -7, number); //rimski brojevi na casovniku: 6
		}
		else if ((int)i == 210) {
			number = "7";
			pDC->TextOutW(-5, -9, number); //rimski brojevi na casovniku: 7
		}
		else if ((int)i == 240) {
			number = "8";
			pDC->TextOutW(-6, -7, number); //rimski brojevi na casovniku: 8
		}
		else if ((int)i == 270) {
			number = "9";
			pDC->TextOutW(-5, -7, number); //rimski brojevi na casovniku: 9
		}
		else if ((int)i == 300) {
			number = "10";
			pDC->TextOutW(-3, -7, number); //rimski brojevi na casovniku: 10
		}
		else if ((int)i == 330) {
			number = "11";
			pDC->TextOutW(-4, -7, number); //rimski brojevi na casovniku: 11
		}

		pDC->SelectObject(oldFont);
		fontNumber.DeleteObject();

		b = SetWorldTransform(pDC->m_hDC, &oldXForm);
		SetGraphicsMode(pDC->m_hDC, prevMode);
	}


	for (float i = 0.0; i < 360.0; i = i + 6.0) {
		prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
		SetTransform(pDC, lokacijaX, lokacijaY, 0.0, -36.0, i + beta, 0.0, &oldXForm); //610, 190 - centar sata

		if ((int)i % 30 == 0)
			pDC->SelectObject(&newPenBlack2); //svaki peti podeok deblji (2px)
		else
			pDC->SelectObject(&newPenBlack1);

		pDC->MoveTo(0, 4);
		pDC->LineTo(0, -4);

		b = SetWorldTransform(pDC->m_hDC, &oldXForm);
		SetGraphicsMode(pDC->m_hDC, prevMode);
	}

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldFont);

#pragma endregion

#pragma region Sat-kazaljka-velika:

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, (float)(m_bHitClockwiseBig * 6), beta, &oldXForm); //610, 190 - centar sata

	WMFName = CString("VelikaKazaljka.emf");
	//HENHMETAFILE MF;
	//ENHMETAHEADER emfHeader;
	MF = GetEnhMetaFile(WMFName);
	GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
	PlayEnhMetaFile(pDC->m_hDC, MF, CRect(-5, -45, 5, 18));
	DeleteEnhMetaFile(MF);

	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

#pragma endregion

#pragma region Sat-kazaljka-mala:

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetTransform(pDC, lokacijaX, lokacijaY, 0.0, 0.0, (float)(m_bHitClockwiseSmall * 30), beta, &oldXForm); //610, 190 - centar sata

	WMFName = CString("MalaKazaljka.emf");
	//HENHMETAFILE MF;
	//ENHMETAHEADER emfHeader;
	MF = GetEnhMetaFile(WMFName);
	GetEnhMetaFileHeader(MF, sizeof(ENHMETAHEADER), &emfHeader);
	PlayEnhMetaFile(pDC->m_hDC, MF, CRect(-10, -40, 10, 18));
	DeleteEnhMetaFile(MF);

	b = SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

#pragma endregion


	///////////////////////////////////////////////////////////////// lab2 ///
}

void Clab1View::SetTransform(CDC * pDC, float cx, float cy, float rx, float ry, float alfa, float beta, XFORM* oldXForm){

	// lab2 ///////////////////////////////////////////////////

	XFORM XForm;
	DWORD dw;
	BOOL b;
	float rad = 3.14159265 * alfa / 180.0;
	float rad2 = 3.14159265 * beta / 180.0;

	b = GetWorldTransform(pDC->m_hDC, oldXForm);


	XForm.eM11 = (FLOAT) cos(rad2);
	XForm.eM12 = (FLOAT) sin(rad2);
	XForm.eM21 = (FLOAT) -sin(rad2);
	XForm.eM22 = (FLOAT) cos(rad2);
	XForm.eDx = (FLOAT) 0.0;
	XForm.eDy = (FLOAT) 0.0;

	b = SetWorldTransform(pDC->m_hDC, &XForm); //rotiranje oko ose
	dw = GetLastError();

	XForm.eM11 = (FLOAT) 1.0;
	XForm.eM12 = (FLOAT) 0.0;
	XForm.eM21 = (FLOAT) 0.0;
	XForm.eM22 = (FLOAT) 1.0;
	XForm.eDx = (FLOAT) rx;
	XForm.eDy = (FLOAT) ry;

	b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //pomeranje na gore
	dw = GetLastError();

	XForm.eM11 = (FLOAT) cos(rad);
	XForm.eM12 = (FLOAT) sin(rad);
	XForm.eM21 = (FLOAT) -sin(rad);
	XForm.eM22 = (FLOAT) cos(rad);
	XForm.eDx = (FLOAT) 0.0;
	XForm.eDy = (FLOAT) 0.0;

	b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //rotacija u smeru kazaljke na satu
	dw = GetLastError();

	XForm.eM11 = (FLOAT) 1.0;
	XForm.eM12 = (FLOAT) 0.0;
	XForm.eM21 = (FLOAT) 0.0;
	XForm.eM22 = (FLOAT) 1.0;
	XForm.eDx = (FLOAT)cx;
	XForm.eDy = (FLOAT)cy;

	b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //pomeranje na krajnju lokaciju
	dw = GetLastError();

	/////////////////////////////////////////////////////// lab2 ////////////

}


void Clab1View::SetBitmapTransform(CDC* pDC, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM* oldXForm) {

	XFORM XForm;
	DWORD dw;
	BOOL b;
	float rad = 3.14159265 * alpha / 180.0;

	b = GetWorldTransform(pDC->m_hDC, oldXForm);

	if (mirror) {
		XForm.eM11 = (FLOAT) -1.0;
		XForm.eM12 = (FLOAT) 0.0;
		XForm.eM21 = (FLOAT) 0.0;
		XForm.eM22 = (FLOAT) 1.0;
		XForm.eDx = (FLOAT) 0.0;
		XForm.eDy = (FLOAT) 0.0;

		b = SetWorldTransform(pDC->m_hDC, &XForm); //odraz u ogledalu po y osi
		dw = GetLastError();
	}

	XForm.eM11 = (FLOAT) scale;
	XForm.eM12 = (FLOAT) 0.0;
	XForm.eM21 = (FLOAT) 0.0;
	XForm.eM22 = (FLOAT) scale;
	XForm.eDx = (FLOAT) 0.0;
	XForm.eDy = (FLOAT) 0.0;

	if (mirror) {
		b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //skaliranje
	}
	else {
		b = SetWorldTransform(pDC->m_hDC, &XForm); //skaliranje
	}

	dw = GetLastError();

	XForm.eM11 = (FLOAT) cos(rad);
	XForm.eM12 = (FLOAT) sin(rad);
	XForm.eM21 = (FLOAT) -sin(rad);
	XForm.eM22 = (FLOAT) cos(rad);
	XForm.eDx = (FLOAT) 0.0;
	XForm.eDy = (FLOAT) 0.0;

	b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //rotacija u smeru kazaljke na satu
	dw = GetLastError();

	XForm.eM11 = (FLOAT) 1.0;
	XForm.eM12 = (FLOAT) 0.0;
	XForm.eM21 = (FLOAT) 0.0;
	XForm.eM22 = (FLOAT) 1.0;
	XForm.eDx = (FLOAT) cx;
	XForm.eDy = (FLOAT) cy;

	b = ModifyWorldTransform(pDC->m_hDC, &XForm, MWT_RIGHTMULTIPLY); //pomeranje na krajnju lokaciju
	dw = GetLastError();

}

COLORREF Clab1View::SetBitmapRGBFilter(CBitmap*bmp, bool r, bool g, bool b) {
	COLORREF color = RGB(255, 255, 255);
	if (r) {
		color = RGB(255, 0, 0);
	}
	if (g) {
		color = RGB(0, 255, 0);
	}
	if (b) {
		color = RGB(0, 0, 255);
	}
	return color;

}

void Clab1View::DrawBitmap(CDC* pDC, int x, int y, float scale, float alpha, CString name) {

	XFORM oldXForm;
	int prevMode;

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetBitmapTransform(pDC, x, y, NULL, NULL, scale, alpha, false, &oldXForm);

	DImage dm;
	dm.Load(name);
	dm.Draw(pDC, CRect(0, 0, dm.Width(), dm.Height()), CRect(-dm.Width()/2.0, -dm.Height()/2.0, dm.Width()/2, dm.Height()/2));
	

	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);

}

void Clab1View::DrawTransparentBitmap(CDC* pDC, int x, int y, float scale, bool r, bool g, bool b, CString name) {
	
	CBitmap bmpImage;
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	bmpImage.Attach(hBmp);

	CBitmap bmpMask;
	BITMAP bm;
	bmpImage.GetBitmap(&bm);

	bmpMask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC* SrcDC = new CDC();
	SrcDC->CreateCompatibleDC(pDC);
	CDC* DstDC = new CDC();
	DstDC->CreateCompatibleDC(pDC);

	CBitmap* pOldSrcBmp = SrcDC->SelectObject(&bmpImage);
	CBitmap* pOldDstBmp = DstDC->SelectObject(&bmpMask);

	//DImage* img = new DImage();   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//img->Load(CString("Part1.bmp"));
	//unsigned char * prom = img->GetDIBBits();
	//COLORREF bojaR = prom[2];
	//COLORREF bojaG = prom[1];
	//COLORREF bojaB = prom[0];
	//////prom[3] bi bilo 00 jer se pamti ovako: 00bbggrr
	//COLORREF clrTopLeft = RGB(bojaR, bojaG, bojaB);

	COLORREF clrTopLeft = SrcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = SrcDC->SetBkColor(clrTopLeft);

	DstDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveDstText = SrcDC->SetTextColor(SetBitmapRGBFilter(NULL, r, g, b));
	SrcDC->SetBkColor(RGB(0, 0, 0));
	SrcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND);

	DstDC->SetTextColor(clrSaveDstText);
	SrcDC->SetBkColor(clrSaveBk);
	SrcDC->SelectObject(pOldSrcBmp);
	DstDC->SelectObject(pOldDstBmp);

	SrcDC->DeleteDC();
	delete SrcDC;
	DstDC->DeleteDC();
	delete DstDC;

	CDC* MemDC = new CDC();
	MemDC->CreateCompatibleDC(NULL);
	CBitmap* bmpOldT = MemDC->SelectObject(&bmpMask);
	pDC->BitBlt(-bm.bmWidth / 2 + x, -bm.bmWidth / 2 + y, bm.bmWidth, bm.bmHeight, MemDC, 0, 0, SRCAND);

	SetBitmapRGBFilter(&bmpImage, r, g, b);
	MemDC->SelectObject(&bmpImage);

	pDC->BitBlt(-bm.bmWidth / 2 + x, -bm.bmWidth / 2 + y, bm.bmWidth, bm.bmHeight, MemDC, 0, 0, SRCPAINT);

	MemDC->SelectObject(bmpOldT);
	MemDC->DeleteDC();
	delete MemDC;

}

void Clab1View::DrawPuzzlePart(CDC* pDC, int x, int y, int cx, int cy, float scale, float angle, bool mirror, bool r, bool g, bool b, CString name) {
	
	XFORM oldXForm;
	int prevMode;

	prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	SetBitmapTransform(pDC, x, y, NULL, NULL, scale, angle, mirror, &oldXForm);

	DrawTransparentBitmap(pDC, cx, cy, NULL, r, g, b, name);

	SetWorldTransform(pDC->m_hDC, &oldXForm);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}


// Clab1View message handlers

void Clab1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CRect rect;
	GetClientRect(&rect);

	double x = rect.Width() / 800.0; //skaliranje sirine zbog map moda
	double y = rect.Height() / 800.0; //skaliranje visine zbog map moda

	CRgn rgnCabinet;
	rgnCabinet.CreateEllipticRgn(85 * x, 365 * y, 95 * x, 375 * y);

	if (rgnCabinet.PtInRegion(point)){
		m_bHitCabinet = true;
		Invalidate();
	}

	CRgn rgnKey;
	rgnKey.CreateRectRgn(55 * x, 515 * y, 80 * x, 545 * y);

	if (rgnKey.PtInRegion(point) && m_bHitCabinet) {
		m_bHitKey = true;
		Invalidate();
	}


	// lab1 vezba na casu ////////////////////////////////////////

	CRgn rgnDrawer; 
	rgnDrawer.CreateRectRgn(95 * x, 700 * y, 105 * x, 710 * y);

	if (rgnDrawer.PtInRegion(point) && m_bHitKey) {
		m_bHitDrawer = true;
		Invalidate();
	}

	CRgn rgnKey2;
	rgnKey2.CreateRectRgn(70 * x, 675 * y, 95 * x, 705 * y);

	if (rgnKey2.PtInRegion(point) && m_bHitDrawer) {
		m_bHitKey2 = true;
		Invalidate();
	}

	////////////////////////////////////// lab1 vezba na casu //



	CRgn rgnDoor;
	rgnDoor.CreateEllipticRgn(756 * x, 455 * y, 779 * x, 479 * y);

	if (rgnDoor.PtInRegion(point) && m_bHitKey2){
		m_bHitDoor = true;
		Invalidate();
	}

	CRgn rgnCurtain;
	rgnCurtain.CreateRectRgn(295 * x, 160 * y, 505 * x, 480 * y);

	if (rgnCurtain.PtInRegion(point)) {
		m_bHitCurtain = true;
		Invalidate();
	}


	CView::OnLButtonDown(nFlags, point);

}

void Clab1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	// lab2 vezba //////////////////////////////////////////////////////////////////

	if (nChar == 'V') {
		m_bHitClockwiseBig = (m_bHitClockwiseBig + 1) % 60;
		m_bHitPendulum = (m_bHitPendulum + 1) % 4;
		Invalidate();
	}

	if (nChar == 'M') {
		m_bHitClockwiseSmall = (m_bHitClockwiseSmall + 1) % 12;
		m_bHitPendulum = (m_bHitPendulum + 1) % 4;
		Invalidate();
	}

	if (nChar == 'O') {
		m_bHitClock = (m_bHitClock + 1) % 12;
		Invalidate();
	}

	if (nChar == 'P') {
		m_bHitClock = (m_bHitClock - 1);
		if (m_bHitClock == -1)
			m_bHitClock = 11;
		Invalidate();
	}

	///////////////////////////////////////////////////////////////// lab2 vezba ///


	// lab3 vezba //////////////////////////////////////////////////////////////////

	if (nChar == 'R') {
		if (m_bHitR)
			m_bHitR = false;
		else {
			m_bHitR = true;
			m_bHitG = false;
			m_bHitB = false;
		}
		Invalidate();
	}

	if (nChar == 'G') {
		if (m_bHitG)
			m_bHitG = false;
		else {
			m_bHitR = false;
			m_bHitG = true;
			m_bHitB = false;
		}
		Invalidate();
	}

	if (nChar == 'B') {
		if (m_bHitB)
			m_bHitB = false;
		else {
			m_bHitR = false;
			m_bHitG = false;
			m_bHitB = true;
		}
		Invalidate();
	}

	///////////////////////////////////////////////////////////////// lab3 vezba ///


	if (nChar == 'Q') {
		m_bHitPicture = (m_bHitPicture + 1) % 12;
		Invalidate();
	}

	if (nChar == 'E') {
		m_bHitPicture = (m_bHitPicture - 1);
		if (m_bHitPicture == -1)
			m_bHitPicture = 11;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


// Clab1View printing

BOOL Clab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Clab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Clab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Clab1View diagnostics

#ifdef _DEBUG
void Clab1View::AssertValid() const
{
	CView::AssertValid();
}

void Clab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab1Doc* Clab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab1Doc)));
	return (Clab1Doc*)m_pDocument;
}
#endif //_DEBUG
