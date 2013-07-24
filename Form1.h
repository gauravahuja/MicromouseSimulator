#pragma once

#include "Micromouse.h"

#include "Element.h"
#include "ElementOps.h"
#include "LinkList.h"
#include "LinkListOps.h"
#include "Node.h"

#define NULL 0

namespace MicromouseSimulator
{
	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	Maze DataMaze;
	Maze PathMaze;
	_Mouse Mouse;	
	int SimulationDelay;


	void DrawMaze(Panel ^pPanel, Maze *DataMazeToDraw = &DataMaze, Color MazeWallColor = Color::Red, Color MazePathColor = Color::Green,bool ShowPath = false, Maze *PathMazeToDraw = &PathMaze, _Mouse *pMouse = &Mouse)
	{
		pPanel->Refresh();

		int Thickness = 1;
		int CellSize = ((pPanel->Height)-17*Thickness)/16;
		int MazeSize = CellSize*16 + 17*Thickness;
		int StartCoord = (pPanel->Height- MazeSize)/2;
		
		int CellTopLeftCoordx = 0;
		int CellTopLeftCoordy = 0;
		int Xshift, Yshift;
		int i, j;
		unsigned char DataMazeCellData = 0;
		unsigned char PathMazeCellData = 0;

		Graphics ^PanelGraphic = pPanel->CreateGraphics();
		Pen ^pPen = gcnew Pen(MazeWallColor, (float)Thickness);
		
		CellSize += Thickness;
		Yshift = CellSize/2;
		Xshift = CellSize/2;

		LinkList PathList = CreateLinkList();
		Element Point;

		for(i = 15; i >= 0; i--)
		{
			CellTopLeftCoordy = StartCoord + (15-i)*(CellSize);

			for(j = 0; j < 16; j++)
			{
				CellTopLeftCoordx = StartCoord + (j)*(CellSize);
				DataMazeCellData = DataMazeToDraw->ucCell[i][j]; 
				if(ShowPath)
				{
					if(PathMazeToDraw->ucCell[i][j])
					{
						Point.x = CellTopLeftCoordx + Xshift;
						Point.y = CellTopLeftCoordy + Yshift;
						Point.Value = PathMazeToDraw->ucCell[i][j];
						PathList = Insert(PathList, Point);
					}
				}

				if(DataMazeCellData & NORTH)
				{
					PanelGraphic->DrawLine(pPen, CellTopLeftCoordx, CellTopLeftCoordy, CellTopLeftCoordx + CellSize, CellTopLeftCoordy);
				}

				if(DataMazeCellData & SOUTH)
				{
					PanelGraphic->DrawLine(pPen, CellTopLeftCoordx, CellTopLeftCoordy + CellSize, CellTopLeftCoordx + CellSize, CellTopLeftCoordy + CellSize);
				}
	
				if(DataMazeCellData & WEST)
				{
					PanelGraphic->DrawLine(pPen, CellTopLeftCoordx, CellTopLeftCoordy, CellTopLeftCoordx, CellTopLeftCoordy + CellSize);
				}			
				
				if(DataMazeCellData & EAST)
				{
					PanelGraphic->DrawLine(pPen, CellTopLeftCoordx + CellSize, CellTopLeftCoordy, CellTopLeftCoordx + CellSize, CellTopLeftCoordy + CellSize);
				}
			}
		}

		PathList = Sort(PathList);
		Link CurrentPoint = NULL;

		delete pPen;
		pPen = gcnew Pen(MazePathColor, (float)Thickness);

		Bitmap ^MousePic;
		switch(pMouse->Head)
		{
		case NORTH:
			MousePic = gcnew Bitmap("MouseN.bmp");
			break;
		case EAST:
			MousePic = gcnew Bitmap("MouseE.bmp");
			break;
		case SOUTH:
			MousePic = gcnew Bitmap("MouseS.bmp");
			break;
		case WEST:
			MousePic = gcnew Bitmap("MouseW.bmp");
			break;
		default:
			MousePic = gcnew Bitmap("MouseN.bmp");
			break;
		}
		MousePic->MakeTransparent(Color::Black);
		Icon ^ MouseIcon = Icon::FromHandle(MousePic->GetHicon());

		if(ShowPath)
		{
			CurrentPoint = PathList.Head;
			PanelGraphic->DrawRectangle(gcnew Pen(Color::White, (float)Thickness), CurrentPoint->E.x, CurrentPoint->E.y, 1, 1);
			PanelGraphic->DrawIcon(MouseIcon, CurrentPoint->E.x - MouseIcon->Width/2, CurrentPoint->E.y - MouseIcon->Height/2);
			while(CurrentPoint->Next != NULL)
			{
				PanelGraphic->DrawLine(pPen, CurrentPoint->E.x, CurrentPoint->E.y, CurrentPoint->Next->E.x, CurrentPoint->Next->E.y);
				CurrentPoint = CurrentPoint->Next;
			}
			PanelGraphic->DrawRectangle(gcnew Pen(Color::Blue, (float)Thickness), CurrentPoint->E.x, CurrentPoint->E.y, 1, 1);
		}
		PathList = DeleteList(PathList);
		delete pPen;
	}	

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:

		System::Windows::Forms::Panel^			pMaze1;
		System::Windows::Forms::Panel^			pMaze2;
		System::Windows::Forms::GroupBox^		gbMazeFile;
		System::Windows::Forms::TextBox^		tbMazeFile;
		System::Windows::Forms::Label^			lMazeFile;
		System::Windows::Forms::Button^			bFindFile;
		System::Windows::Forms::OpenFileDialog^	ofdFindFile;
		System::Windows::Forms::StatusStrip^	ssStatus;
		System::Windows::Forms::GroupBox^		gbRTContols;
		System::Windows::Forms::Button^			bResetMousePostion;
		System::Windows::Forms::Button^			bDecreaseSimulationSpeed;
		System::Windows::Forms::Button^			bIncreaseSimulationSpeed;
		System::Windows::Forms::ProgressBar^	pbSimulationSpeed;
		System::Windows::Forms::Label^			lSimulationSpeed;
		System::Windows::Forms::Button^			bStopSimulation;
		System::Windows::Forms::Button^			bStartSimulation;
		System::Windows::Forms::GroupBox^		gbSelectSimulationMode;
		System::Windows::Forms::RadioButton^	rbRealTimeSimulation;
		System::Windows::Forms::RadioButton^	rbFindPathBetweenTwoPoints;
		System::Windows::Forms::GroupBox^		gbPathControl;
		System::Windows::Forms::TextBox^		tbDestinationY;
		System::Windows::Forms::Label^			lDestinationY;
		System::Windows::Forms::TextBox^		tbDestinationX;
		System::Windows::Forms::Label^			lDestinationX;
		System::Windows::Forms::TextBox^		tbSourceY;
		System::Windows::Forms::Label^			lSourceY;
		System::Windows::Forms::TextBox^		tbSourceX;
		System::Windows::Forms::Label^			lSourceX;
		System::Windows::Forms::Button^			bFind;
		System::Windows::Forms::ToolStripStatusLabel^  slStatus;

	private: System::ComponentModel::IContainer^  components;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pMaze1 = (gcnew System::Windows::Forms::Panel());
			this->pMaze2 = (gcnew System::Windows::Forms::Panel());
			this->gbMazeFile = (gcnew System::Windows::Forms::GroupBox());
			this->bFindFile = (gcnew System::Windows::Forms::Button());
			this->tbMazeFile = (gcnew System::Windows::Forms::TextBox());
			this->lMazeFile = (gcnew System::Windows::Forms::Label());
			this->ofdFindFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ssStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->slStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->gbRTContols = (gcnew System::Windows::Forms::GroupBox());
			this->bResetMousePostion = (gcnew System::Windows::Forms::Button());
			this->bDecreaseSimulationSpeed = (gcnew System::Windows::Forms::Button());
			this->bIncreaseSimulationSpeed = (gcnew System::Windows::Forms::Button());
			this->pbSimulationSpeed = (gcnew System::Windows::Forms::ProgressBar());
			this->lSimulationSpeed = (gcnew System::Windows::Forms::Label());
			this->bStopSimulation = (gcnew System::Windows::Forms::Button());
			this->bStartSimulation = (gcnew System::Windows::Forms::Button());
			this->gbSelectSimulationMode = (gcnew System::Windows::Forms::GroupBox());
			this->rbRealTimeSimulation = (gcnew System::Windows::Forms::RadioButton());
			this->rbFindPathBetweenTwoPoints = (gcnew System::Windows::Forms::RadioButton());
			this->gbPathControl = (gcnew System::Windows::Forms::GroupBox());
			this->bFind = (gcnew System::Windows::Forms::Button());
			this->tbDestinationY = (gcnew System::Windows::Forms::TextBox());
			this->lDestinationY = (gcnew System::Windows::Forms::Label());
			this->tbDestinationX = (gcnew System::Windows::Forms::TextBox());
			this->lDestinationX = (gcnew System::Windows::Forms::Label());
			this->tbSourceY = (gcnew System::Windows::Forms::TextBox());
			this->lSourceY = (gcnew System::Windows::Forms::Label());
			this->tbSourceX = (gcnew System::Windows::Forms::TextBox());
			this->lSourceX = (gcnew System::Windows::Forms::Label());
			this->gbMazeFile->SuspendLayout();
			this->ssStatus->SuspendLayout();
			this->gbRTContols->SuspendLayout();
			this->gbSelectSimulationMode->SuspendLayout();
			this->gbPathControl->SuspendLayout();
			this->SuspendLayout();
			// 
			// pMaze1
			// 
			this->pMaze1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pMaze1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pMaze1->Location = System::Drawing::Point(12, 12);
			this->pMaze1->Name = L"pMaze1";
			this->pMaze1->Size = System::Drawing::Size(300, 300);
			this->pMaze1->TabIndex = 0;
			// 
			// pMaze2
			// 
			this->pMaze2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pMaze2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pMaze2->Location = System::Drawing::Point(322, 12);
			this->pMaze2->Name = L"pMaze2";
			this->pMaze2->Size = System::Drawing::Size(300, 300);
			this->pMaze2->TabIndex = 0;
			// 
			// gbMazeFile
			// 
			this->gbMazeFile->BackColor = System::Drawing::Color::Transparent;
			this->gbMazeFile->Controls->Add(this->bFindFile);
			this->gbMazeFile->Controls->Add(this->tbMazeFile);
			this->gbMazeFile->Controls->Add(this->lMazeFile);
			this->gbMazeFile->Location = System::Drawing::Point(12, 329);
			this->gbMazeFile->Name = L"gbMazeFile";
			this->gbMazeFile->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->gbMazeFile->Size = System::Drawing::Size(200, 92);
			this->gbMazeFile->TabIndex = 0;
			this->gbMazeFile->TabStop = false;
			this->gbMazeFile->Text = L"Maze";
			// 
			// bFindFile
			// 
			this->bFindFile->Location = System::Drawing::Point(62, 51);
			this->bFindFile->Name = L"bFindFile";
			this->bFindFile->Size = System::Drawing::Size(125, 25);
			this->bFindFile->TabIndex = 1;
			this->bFindFile->Text = L"Find File";
			this->bFindFile->UseVisualStyleBackColor = true;
			this->bFindFile->Click += gcnew System::EventHandler(this, &Form1::bFindFile_Click);
			// 
			// tbMazeFile
			// 
			this->tbMazeFile->Location = System::Drawing::Point(62, 24);
			this->tbMazeFile->Name = L"tbMazeFile";
			this->tbMazeFile->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tbMazeFile->Size = System::Drawing::Size(125, 20);
			this->tbMazeFile->TabIndex = 0;
			this->tbMazeFile->TabStop = false;
			// 
			// lMazeFile
			// 
			this->lMazeFile->AutoSize = true;
			this->lMazeFile->Location = System::Drawing::Point(8, 27);
			this->lMazeFile->Name = L"lMazeFile";
			this->lMazeFile->Size = System::Drawing::Size(52, 13);
			this->lMazeFile->TabIndex = 0;
			this->lMazeFile->Text = L"Maze File";
			// 
			// ofdFindFile
			// 
			this->ofdFindFile->Filter = L"Maze Files (*.maz)|*.maz|Maze Files (*.maze)|*.maze";
			this->ofdFindFile->Title = L"Find Maze File";
			// 
			// ssStatus
			// 
			this->ssStatus->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
			this->ssStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->slStatus});
			this->ssStatus->Location = System::Drawing::Point(0, 672);
			this->ssStatus->Name = L"ssStatus";
			this->ssStatus->Size = System::Drawing::Size(634, 22);
			this->ssStatus->Stretch = false;
			this->ssStatus->TabIndex = 0;
			// 
			// slStatus
			// 
			this->slStatus->Name = L"slStatus";
			this->slStatus->Size = System::Drawing::Size(265, 17);
			this->slStatus->Text = L"Micromouse Simulator Created By: Gaurav Ahuja";
			// 
			// gbRTContols
			// 
			this->gbRTContols->Controls->Add(this->bResetMousePostion);
			this->gbRTContols->Controls->Add(this->bDecreaseSimulationSpeed);
			this->gbRTContols->Controls->Add(this->bIncreaseSimulationSpeed);
			this->gbRTContols->Controls->Add(this->pbSimulationSpeed);
			this->gbRTContols->Controls->Add(this->lSimulationSpeed);
			this->gbRTContols->Controls->Add(this->bStopSimulation);
			this->gbRTContols->Controls->Add(this->bStartSimulation);
			this->gbRTContols->Enabled = false;
			this->gbRTContols->Location = System::Drawing::Point(12, 530);
			this->gbRTContols->Name = L"gbRTContols";
			this->gbRTContols->Size = System::Drawing::Size(405, 131);
			this->gbRTContols->TabIndex = 1;
			this->gbRTContols->TabStop = false;
			this->gbRTContols->Text = L"Real Time Simulation Mode Contols";
			// 
			// bResetMousePostion
			// 
			this->bResetMousePostion->Location = System::Drawing::Point(278, 30);
			this->bResetMousePostion->Name = L"bResetMousePostion";
			this->bResetMousePostion->Size = System::Drawing::Size(120, 25);
			this->bResetMousePostion->TabIndex = 6;
			this->bResetMousePostion->Text = L"Reset Mouse Postion";
			this->bResetMousePostion->UseVisualStyleBackColor = true;
			// 
			// bDecreaseSimulationSpeed
			// 
			this->bDecreaseSimulationSpeed->Location = System::Drawing::Point(170, 97);
			this->bDecreaseSimulationSpeed->Name = L"bDecreaseSimulationSpeed";
			this->bDecreaseSimulationSpeed->Size = System::Drawing::Size(30, 25);
			this->bDecreaseSimulationSpeed->TabIndex = 7;
			this->bDecreaseSimulationSpeed->Text = L"-";
			this->bDecreaseSimulationSpeed->UseVisualStyleBackColor = true;
			this->bDecreaseSimulationSpeed->Click += gcnew System::EventHandler(this, &Form1::bDecreaseSimulationSpeed_Click);
			// 
			// bIncreaseSimulationSpeed
			// 
			this->bIncreaseSimulationSpeed->BackColor = System::Drawing::Color::Transparent;
			this->bIncreaseSimulationSpeed->Location = System::Drawing::Point(209, 97);
			this->bIncreaseSimulationSpeed->Name = L"bIncreaseSimulationSpeed";
			this->bIncreaseSimulationSpeed->Size = System::Drawing::Size(30, 25);
			this->bIncreaseSimulationSpeed->TabIndex = 8;
			this->bIncreaseSimulationSpeed->Text = L"+";
			this->bIncreaseSimulationSpeed->UseVisualStyleBackColor = false;
			this->bIncreaseSimulationSpeed->Click += gcnew System::EventHandler(this, &Form1::bIncreaseSimulationSpeed_Click);
			// 
			// pbSimulationSpeed
			// 
			this->pbSimulationSpeed->Location = System::Drawing::Point(103, 66);
			this->pbSimulationSpeed->Name = L"pbSimulationSpeed";
			this->pbSimulationSpeed->Size = System::Drawing::Size(200, 25);
			this->pbSimulationSpeed->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->pbSimulationSpeed->TabIndex = 0;
			// 
			// lSimulationSpeed
			// 
			this->lSimulationSpeed->AutoSize = true;
			this->lSimulationSpeed->Location = System::Drawing::Point(8, 78);
			this->lSimulationSpeed->Name = L"lSimulationSpeed";
			this->lSimulationSpeed->Size = System::Drawing::Size(89, 13);
			this->lSimulationSpeed->TabIndex = 0;
			this->lSimulationSpeed->Text = L"Simulation Speed";
			// 
			// bStopSimulation
			// 
			this->bStopSimulation->Location = System::Drawing::Point(144, 30);
			this->bStopSimulation->Name = L"bStopSimulation";
			this->bStopSimulation->Size = System::Drawing::Size(120, 25);
			this->bStopSimulation->TabIndex = 5;
			this->bStopSimulation->Text = L"Stop Simulation";
			this->bStopSimulation->UseVisualStyleBackColor = true;
			// 
			// bStartSimulation
			// 
			this->bStartSimulation->Location = System::Drawing::Point(11, 30);
			this->bStartSimulation->Name = L"bStartSimulation";
			this->bStartSimulation->Size = System::Drawing::Size(120, 25);
			this->bStartSimulation->TabIndex = 4;
			this->bStartSimulation->Text = L"Start Simulation";
			this->bStartSimulation->UseVisualStyleBackColor = true;
			this->bStartSimulation->Click += gcnew System::EventHandler(this, &Form1::bStartSimulation_Click);
			// 
			// gbSelectSimulationMode
			// 
			this->gbSelectSimulationMode->Controls->Add(this->rbRealTimeSimulation);
			this->gbSelectSimulationMode->Controls->Add(this->rbFindPathBetweenTwoPoints);
			this->gbSelectSimulationMode->Location = System::Drawing::Point(220, 329);
			this->gbSelectSimulationMode->Name = L"gbSelectSimulationMode";
			this->gbSelectSimulationMode->Size = System::Drawing::Size(196, 92);
			this->gbSelectSimulationMode->TabIndex = 2;
			this->gbSelectSimulationMode->TabStop = false;
			this->gbSelectSimulationMode->Text = L"SelectSimulationMode";
			// 
			// rbRealTimeSimulation
			// 
			this->rbRealTimeSimulation->AutoSize = true;
			this->rbRealTimeSimulation->Location = System::Drawing::Point(6, 51);
			this->rbRealTimeSimulation->Name = L"rbRealTimeSimulation";
			this->rbRealTimeSimulation->Size = System::Drawing::Size(124, 17);
			this->rbRealTimeSimulation->TabIndex = 3;
			this->rbRealTimeSimulation->Text = L"Real Time Simulation";
			this->rbRealTimeSimulation->UseVisualStyleBackColor = true;
			this->rbRealTimeSimulation->CheckedChanged += gcnew System::EventHandler(this, &Form1::rbRealTimeSimulation_CheckedChanged);
			// 
			// rbFindPathBetweenTwoPoints
			// 
			this->rbFindPathBetweenTwoPoints->AutoSize = true;
			this->rbFindPathBetweenTwoPoints->Checked = true;
			this->rbFindPathBetweenTwoPoints->Location = System::Drawing::Point(6, 25);
			this->rbFindPathBetweenTwoPoints->Name = L"rbFindPathBetweenTwoPoints";
			this->rbFindPathBetweenTwoPoints->Size = System::Drawing::Size(171, 17);
			this->rbFindPathBetweenTwoPoints->TabIndex = 2;
			this->rbFindPathBetweenTwoPoints->TabStop = true;
			this->rbFindPathBetweenTwoPoints->Text = L"Find Path Between Two Points";
			this->rbFindPathBetweenTwoPoints->UseVisualStyleBackColor = true;
			this->rbFindPathBetweenTwoPoints->CheckedChanged += gcnew System::EventHandler(this, &Form1::rbFindPathBetweenTwoPoints_CheckedChanged);
			// 
			// gbPathControl
			// 
			this->gbPathControl->Controls->Add(this->bFind);
			this->gbPathControl->Controls->Add(this->tbDestinationY);
			this->gbPathControl->Controls->Add(this->lDestinationY);
			this->gbPathControl->Controls->Add(this->tbDestinationX);
			this->gbPathControl->Controls->Add(this->lDestinationX);
			this->gbPathControl->Controls->Add(this->tbSourceY);
			this->gbPathControl->Controls->Add(this->lSourceY);
			this->gbPathControl->Controls->Add(this->tbSourceX);
			this->gbPathControl->Controls->Add(this->lSourceX);
			this->gbPathControl->Location = System::Drawing::Point(12, 427);
			this->gbPathControl->Name = L"gbPathControl";
			this->gbPathControl->Size = System::Drawing::Size(404, 97);
			this->gbPathControl->TabIndex = 3;
			this->gbPathControl->TabStop = false;
			this->gbPathControl->Text = L"Path Controls";
			// 
			// bFind
			// 
			this->bFind->Location = System::Drawing::Point(163, 68);
			this->bFind->Name = L"bFind";
			this->bFind->Size = System::Drawing::Size(75, 23);
			this->bFind->TabIndex = 8;
			this->bFind->Text = L"Find";
			this->bFind->UseVisualStyleBackColor = true;
			this->bFind->Click += gcnew System::EventHandler(this, &Form1::bFind_Click);
			// 
			// tbDestinationY
			// 
			this->tbDestinationY->Location = System::Drawing::Point(273, 43);
			this->tbDestinationY->MaxLength = 2;
			this->tbDestinationY->Name = L"tbDestinationY";
			this->tbDestinationY->Size = System::Drawing::Size(125, 20);
			this->tbDestinationY->TabIndex = 7;
			// 
			// lDestinationY
			// 
			this->lDestinationY->AutoSize = true;
			this->lDestinationY->Location = System::Drawing::Point(201, 46);
			this->lDestinationY->Name = L"lDestinationY";
			this->lDestinationY->Size = System::Drawing::Size(70, 13);
			this->lDestinationY->TabIndex = 6;
			this->lDestinationY->Text = L"Destination Y";
			// 
			// tbDestinationX
			// 
			this->tbDestinationX->Location = System::Drawing::Point(273, 17);
			this->tbDestinationX->MaxLength = 2;
			this->tbDestinationX->Name = L"tbDestinationX";
			this->tbDestinationX->Size = System::Drawing::Size(125, 20);
			this->tbDestinationX->TabIndex = 5;
			// 
			// lDestinationX
			// 
			this->lDestinationX->AutoSize = true;
			this->lDestinationX->Location = System::Drawing::Point(201, 20);
			this->lDestinationX->Name = L"lDestinationX";
			this->lDestinationX->Size = System::Drawing::Size(70, 13);
			this->lDestinationX->TabIndex = 4;
			this->lDestinationX->Text = L"Destination X";
			// 
			// tbSourceY
			// 
			this->tbSourceY->Location = System::Drawing::Point(61, 43);
			this->tbSourceY->MaxLength = 2;
			this->tbSourceY->Name = L"tbSourceY";
			this->tbSourceY->Size = System::Drawing::Size(125, 20);
			this->tbSourceY->TabIndex = 3;
			// 
			// lSourceY
			// 
			this->lSourceY->AutoSize = true;
			this->lSourceY->Location = System::Drawing::Point(7, 46);
			this->lSourceY->Name = L"lSourceY";
			this->lSourceY->Size = System::Drawing::Size(51, 13);
			this->lSourceY->TabIndex = 2;
			this->lSourceY->Text = L"Source Y";
			// 
			// tbSourceX
			// 
			this->tbSourceX->Location = System::Drawing::Point(61, 17);
			this->tbSourceX->MaxLength = 2;
			this->tbSourceX->Name = L"tbSourceX";
			this->tbSourceX->Size = System::Drawing::Size(125, 20);
			this->tbSourceX->TabIndex = 1;
			this->tbSourceX->Tag = L"";
			// 
			// lSourceX
			// 
			this->lSourceX->AutoSize = true;
			this->lSourceX->Location = System::Drawing::Point(7, 20);
			this->lSourceX->Name = L"lSourceX";
			this->lSourceX->Size = System::Drawing::Size(51, 13);
			this->lSourceX->TabIndex = 0;
			this->lSourceX->Text = L"Source X";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(634, 694);
			this->Controls->Add(this->gbPathControl);
			this->Controls->Add(this->gbSelectSimulationMode);
			this->Controls->Add(this->gbRTContols);
			this->Controls->Add(this->ssStatus);
			this->Controls->Add(this->gbMazeFile);
			this->Controls->Add(this->pMaze2);
			this->Controls->Add(this->pMaze1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Micromouse Simulator";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->gbMazeFile->ResumeLayout(false);
			this->gbMazeFile->PerformLayout();
			this->ssStatus->ResumeLayout(false);
			this->ssStatus->PerformLayout();
			this->gbRTContols->ResumeLayout(false);
			this->gbRTContols->PerformLayout();
			this->gbSelectSimulationMode->ResumeLayout(false);
			this->gbSelectSimulationMode->PerformLayout();
			this->gbPathControl->ResumeLayout(false);
			this->gbPathControl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
		private: System::Void bFindFile_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 ofdFindFile->ShowDialog();
			 tbMazeFile->Text = ofdFindFile->FileName;
	 
			 char *pFilePath;
			 pFilePath = (char*)(void*)Marshal::StringToHGlobalAnsi(tbMazeFile->Text);

			 if(ReadMazeFile(pFilePath, &DataMaze) == false && tbMazeFile->Text->Length!=0)
			 {
				 MessageBox::Show(L"Invalid Maze File", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 tbMazeFile->Text = L"";
			 }
			 DrawMaze(pMaze1, &DataMaze);
		}

		private: System::Void bIncreaseSimulationSpeed_Click(System::Object^  sender, System::EventArgs^  e)
		{
			 if(pbSimulationSpeed->Value > pbSimulationSpeed->Maximum - 10)
			 {
				 pbSimulationSpeed->Value = pbSimulationSpeed->Maximum;
			 }
			 else
			 {
				 pbSimulationSpeed->Value += 10;
			 }
		}

		private: System::Void bDecreaseSimulationSpeed_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 if(pbSimulationSpeed->Value < pbSimulationSpeed->Minimum + 10)
			 {
				 pbSimulationSpeed->Value = pbSimulationSpeed->Minimum;
			 }
			 else
			 {
				 pbSimulationSpeed->Value -= 10;
			 }
		}

		private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		{
		}
		private: System::Void rbRealTimeSimulation_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			 if(rbRealTimeSimulation->Checked)
			 {
				 gbRTContols->Enabled = true;
				 pbSimulationSpeed->Enabled = true;
			 }
			 else if(rbRealTimeSimulation->Checked == false)
			 {
				 gbRTContols->Enabled = false;
				 pbSimulationSpeed->Enabled = false;
			 }
			 slStatus->Text = L"Real Time Simulation Controls Activated";
			 
		}
		private: System::Void rbFindPathBetweenTwoPoints_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			 if(rbFindPathBetweenTwoPoints->Checked)
			 {
				 gbPathControl->Enabled = true;
			 }
			 else if(rbFindPathBetweenTwoPoints->Checked == false)
			 {
				 gbPathControl->Enabled = false;
			 }
			 slStatus->Text = L"Path Finder Controls Activated";
		}
		private: System::Void bFind_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if((tbDestinationX->Text->Length == 0) || (tbDestinationY->Text->Length == 0) || (tbSourceX->Text->Length == 0) || (tbSourceY->Text->Length == 0))
			{
				slStatus->Text = L"Please Enter Valid Coordinates";
			}
			else
			{
				unsigned char DestinationX = (unsigned char)(Int32::Parse(tbDestinationX->Text)-1);
				unsigned char DestinationY = (unsigned char)(Int32::Parse(tbDestinationY->Text)-1);
				unsigned char SourceX = (unsigned char)(Int32::Parse(tbSourceX->Text)-1);
				unsigned char SourceY = (unsigned char)(Int32::Parse(tbSourceY->Text)-1);
				bool input = false;
				if((DestinationX >= 0) && (DestinationY >= 0) && (SourceX >= 0) && (SourceY >= 0))
				{
					if((DestinationX < 16) && (DestinationY < 16) && (SourceX < 16) && (SourceY < 16))
					{
						input = true;
					}
				}
				if(input == false)
				{
					slStatus->Text = L"Invalid Coordinates. Coordinates should be from 1-16.";
				}
				else
				{
					Mouse.Head = NORTH;
					Mouse.Status = SOLVING;
					Mouse.X = SourceX;
					Mouse.Y = SourceY;
					slStatus->Text = L"Finding and Analyzing path";
					FindPath(SourceX, SourceY, DestinationX, DestinationY, &PathMaze, &DataMaze, &Mouse);
					Mouse.Status = SOLVED;
					slStatus->Text = L"Drawing Maze and selected path";
					DrawMaze(pMaze2, &DataMaze, Color::Red, Color::Green, true);
					slStatus->Text = L"Maze and Path drawn";
				}
			}
		}
		private: System::Void bStartSimulation_Click(System::Object^  sender, System::EventArgs^  e)
		{
		}
};
}

