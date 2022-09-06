#pragma once


#include "hmm_header_file.h"
namespace HMM_GUI_1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
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
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Button^  button7;
	private: System::ComponentModel::IContainer^  components;

	private:
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
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(309, 114);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(162, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Train the model...";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::MidnightBlue;
			this->button1->Location = System::Drawing::Point(325, 384);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(216, 44);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Train Model";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::OrangeRed;
			this->button2->Location = System::Drawing::Point(112, 465);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(254, 34);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Test Model (Seen Data) ";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::Color::OrangeRed;
			this->button3->Location = System::Drawing::Point(494, 465);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(272, 34);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Test Model (Uneen Data)";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(309, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(223, 25);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Model not Trained yet !! ";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button4->Location = System::Drawing::Point(283, 294);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(326, 38);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Record Speech";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->label3->Font = (gcnew System::Drawing::Font(L"Ink Draft", 44, static_cast<System::Drawing::FontStyle>(((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic) 
				| System::Drawing::FontStyle::Strikeout)), System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Red;
			this->label3->Location = System::Drawing::Point(248, 175);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(223, 107);
			this->label3->TabIndex = 6;
			this->label3->Text = L"BOOK";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button5->ForeColor = System::Drawing::Color::LimeGreen;
			this->button5->Location = System::Drawing::Point(575, 208);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(101, 34);
			this->button5->TabIndex = 7;
			this->button5->Text = L"Refresh";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(129, 222);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(87, 20);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Captcha :-";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(564, 405);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(137, 23);
			this->progressBar1->TabIndex = 9;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Form1::progressBar1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(735, 408);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(130, 20);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Not trained yet...";
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button6->Location = System::Drawing::Point(750, 210);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(115, 32);
			this->button6->TabIndex = 11;
			this->button6->Text = L"Action";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(619, 246);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 17);
			this->label6->TabIndex = 12;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(300, 335);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(264, 20);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Live testing (Say the captcha text)";
			this->label7->Click += gcnew System::EventHandler(this, &Form1::label7_Click);
			// 
			// button7
			// 
			this->button7->FlatAppearance->BorderSize = 0;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, static_cast<System::Drawing::FontStyle>(((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic) 
				| System::Drawing::FontStyle::Underline)), System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button7->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->button7->Location = System::Drawing::Point(701, 26);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(190, 48);
			this->button7->TabIndex = 14;
			this->button7->Text = L"Guidelines";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(903, 538);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = L"Form1";
			this->Text = L"Captcha Project";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		static int to_be_recognized=0;
		static int is_correct = 0;
		static int is_trained = 0;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {				 
				 if(!is_trained){
				 read_codebook();
				 
				 timer1->Start();
				 train(1);
				 train(2);
				 train(3);

				 is_trained = 1;
				 
				 label1->Text = "...";
				 label2->Text = "Training Completed !!!";
				 label5->Text = "Model is trained !!!";
				 }
				 
			 }


	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(is_trained){
					 label2->Text = "Testing with seen data .....";				 
					 test();
					 label1->Text = "Overall accuracy is :- " + get_overall_accuracy().ToString() + " %";
				 }
				 
			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (is_trained){
				 label2->Text = "Testing with unseen data .....";				 
				 test_offline();
				 label1->Text = "Overall accuracy is :- " + get_overall_accuracy().ToString() + " %";
			 }
			 
		 }

private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 label2->Text = "Live testing ...";				 
			 
			 int recognized_digit = test_livedata();
			 
			 	 

			 switch(recognized_digit){
			 case 0:
				 label1->Text = "Recognized word is -	BOOK";
				 break;
			 case 1:
				 label1->Text = "Recognized word is -	DOWN";
				 break;
			 case 2:
				 label1->Text = "Recognized word is -	BUT";
				 break;
			 case 3:
				 label1->Text = "Recognized word is -	BATTLE";
				 break;
			 case 4:
				 label1->Text = "Recognized word is -	ROSES";
				 break;
			 case 5:
				 label1->Text = "Recognized word is -	FAT";
				 break;
			 case 6:
				 label1->Text = "Recognized word is -	ZOO";
				 break;
			 case 7:
				 label1->Text = "Recognized word is -	KIT";
				 break;
			 case 8:
				 label1->Text = "Recognized word is -	SING";
				 break;
			 case 9:
				 label1->Text = "Recognized word is -	RENT";
				 break;
			 default:
				 label1->Text = " ";
				 break;
			 }

			 if(recognized_digit == to_be_recognized){
				 label1->Text += " -----> CORRECT !!!" ;
				 is_correct = 1;
				 
			 }
			 else{
				 label1->Text += " -----> INCORRECT !!!" ;
				 is_correct = 0;
			 }

			 

		 }
		 
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 int rand_num = get_rand_num();

			 switch(rand_num){
			 case 0:
				 label3->Text = " BOOK";
				 break;
			 case 1:
				 label3->Text = " DOWN";
				 break;
			 
			 case 2:
				 label3->Text = " BUT";
				 break;
			 case 3:
				 label3->Text = " BATTLE";
				 break;
			 case 4:
				 label3->Text = " ROSES";
				 break;
			 
			 case 5:
				 label3->Text = " FAT";
				 break;
			 case 6:
				 label3->Text = " ZOO";
				 break;
			 case 7:
				 label3->Text = " KIT";
				 break;
			 case 8:
				 label3->Text = " SING";
				 break;
			 case 9:
				 label3->Text = " RENT";
				 break;
			 default:
				 label3->Text = " ";
				 break;
			 }
			 //label3->Text = rand_num.ToString();
			 to_be_recognized = rand_num;
		 }


private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 progressBar1->Increment(1);
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(is_correct){
				 system("start https://www.google.com/");
				 label6->Text = "";
			 }
			 else{
				 label6->Text = "Captcha is not correct !!! Please try again..";
			 }
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
			 system("start notepad 'guideline.txt'");

		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

