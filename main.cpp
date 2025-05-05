#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextstyles.h>
#include <wx/richtext/richtextxml.h>
#include <wx/sizer.h>
#include <wx/button.h> 

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);
private:
	wxRichTextCtrl* m_richTextCtrlLeft;
	wxRichTextCtrl* m_richTextCtrlRight;

	wxButton* m_button1;
	wxButton* m_button2;
	wxButton* m_button3;

	void OnButton1Click(wxCommandEvent& event);
	void OnButton2Click(wxCommandEvent& event);
	void OnButton3Click(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);

	MyFrame *frame = new MyFrame("WordChecker");
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600))
{
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);

	m_richTextCtrlLeft = new wxRichTextCtrl(mainPanel, wxID_ANY, wxEmptyString,
	                                        wxDefaultPosition, wxDefaultSize,
	                                        wxVSCROLL | wxHSCROLL | wxBORDER_SUNKEN);

	m_richTextCtrlRight = new wxRichTextCtrl(mainPanel, wxID_ANY, wxEmptyString,
	                                         wxDefaultPosition, wxDefaultSize,
	                                         wxVSCROLL | wxHSCROLL | wxBORDER_SUNKEN 
	                                         | wxTE_READONLY);
	
	int button1Id = wxID_HIGHEST + 1;
	int button2Id = wxID_HIGHEST + 2;
	int button3Id = wxID_HIGHEST + 3;

	m_button1 = new wxButton(mainPanel, wxID_HIGHEST + 1, "Kontrol Et");
	m_button2 = new wxButton(mainPanel, wxID_HIGHEST + 2, "Kaydet");
	m_button3 = new wxButton(mainPanel, wxID_HIGHEST + 3, "Ayarlar");

	// --- Sizers ---
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxVERTICAL);
	buttonSizer->Add(
		m_button1,
		0,                	// Proportion 0: Button doesn't grow vertically
		wxEXPAND | wxBOTTOM,// Flag: Expand horizontally to fill column, add space below
		5                 	// Border size
	);
	buttonSizer->Add(
		m_button2,
		0,                	// Proportion 0: Button doesn't grow vertically
		wxEXPAND | wxBOTTOM,// Flag: Expand horizontally to fill column
		5                 	// Border size (no border below the last button)
	);
	buttonSizer->Add(         // <-- ADD THIS BLOCK
		m_button3,
		0,                    // Proportion 0
		wxEXPAND,             // Flag: Expand horizontally
		0                     // Border size (0, since it's the last one for now)
	);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

	mainSizer->Add(
		m_richTextCtrlLeft,
		1,                      // Proportion 1: Takes half of the resizable space
		wxEXPAND | wxALL,       // Flags: Expand fully, add border on all sides
		5                       // Border size
	);

	mainSizer->Add(
		m_richTextCtrlRight,
		1,                      // Proportion 1: Takes the other half of resizable space
		wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, // Flags: Expand, add border on 3 sides
		5                       // Border size (leave right side open for buttons)
	);

	mainSizer->Add(
		buttonSizer,
		0,                      // Proportion 0: Button column takes minimum width, doesn't resize horizontally
		wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, // Flags: Allow vertical expansion within its cell, add border on 3 sides
		5                       // Border size
	);

	mainPanel->SetSizer(mainSizer);

	// Create a sizer for the frame itself to hold the mainPanel
	// This ensures the panel resizes correctly with the frame
	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->Add(mainPanel, 1, wxEXPAND | wxALL, 0); // Panel expands to fill frame
	this->SetSizerAndFit(frameSizer); // Set sizer for the frame

	this->SetMinSize(wxSize(500, 300));

	// --- Sizers ---
	m_richTextCtrlRight->BeginBold();
	m_richTextCtrlRight->WriteText("Kontrol Et tusuna bas!"); // Turkish character support required
	m_richTextCtrlRight->EndBold();

	mainPanel->Bind(wxEVT_BUTTON, &MyFrame::OnButton1Click, this, button1Id);
	mainPanel->Bind(wxEVT_BUTTON, &MyFrame::OnButton2Click, this, button2Id);
	mainPanel->Bind(wxEVT_BUTTON, &MyFrame::OnButton3Click, this, button3Id);
}

void MyFrame::OnButton1Click(wxCommandEvent& even)
{
	wxString textFromLeft = m_richTextCtrlLeft->GetValue();

	// vvv Check Happens Here vvv
	constexpr std::array<char, 2> blocked_characters{'\n', '\t'};


	std::cout << blocked_characters.at(0) << std::endl;

	std::string text = textFromLeft.utf8_string();

	std::cout << text << std::endl; 
	std::cout << std::endl;

	std::replace(text.begin(), text.end(), '\n', ' ');
	std::replace(text.begin(), text.end(), '\t', ' ');

	text += " ";

	std::vector<std::pair<std::string,int>> index;

	// Seperate the sentence into words
	bool did_it = false;
	int how_much_did = 0;
	std::string word;
	for(int i = 0; i < text.size(); i++){
		if(did_it && text.at(i) == ' '){
			index.push_back({word,1});
			word = "";
		}
		if(text.at(i) == ' '){
			did_it = false;
		}
		else{
			word += text.at(i);
			did_it = true;
			how_much_did++;
		}
	}
	text = "";

	for(int i = 0; i < index.size(); i++)
	{
		std::cout << std::get<0>(index.at(i)) << " : " << std::get<1>(index.at(i)) << std::endl;
	}

	if(how_much_did == 0){
		wxLogMessage("Lutfen soldaki kutuya bir seyler yaz!");
		return;
	}

	if(index.size() == 1){
		text += std::get<0>(index.at(0)) + " : 1\n";
		textFromLeft = wxString::FromUTF8(text);
		m_richTextCtrlRight->SetValue(textFromLeft);
		return;
	}

	//for(int i = 0; i < index.size()-1; i++){
	//	for(int j = 0; j < index.size()-1-i; j++){
	//		if(std::get<0>(index.at(j)) > std::get<0>(index.at(j+1))){
	//			std::swap(index.at(j), index.at(j+1));
	//		}
	//	}
	//}
	
	std::sort(index.begin(), index.end());

	index.push_back({"",0});
	int count{0};
	for(int i = 0; i < index.size()-1; i++){
		if(std::get<0>(index.at(i)) == std::get<0>(index.at(i+1))){
			index.erase(index.begin() + i);
			i -= 1;
			count++;
		}
		else{
			std::get<1>(index.at(i)) += count;
			count = 0;
		}
	}

	index.pop_back();

	//for(int i = 0; i < index.size()-1; i++){
	//	for(int j = 0; j < index.size()-1-i; j++){
	//		if(std::get<1>(index.at(j)) < std::get<1>(index.at(j+1))){
	//			std::swap(index.at(j), index.at(j+1));
	//		}
	//	}
	//}
	
	std::sort(index.begin(), index.end(),
    [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first > b.first;
    });

	for(int i = 0; i < index.size(); i++){
		text += std::get<0>(index.at(i)) + " : " + std::to_string(std::get<1>(index.at(i))) + '\n';
	}

	textFromLeft = wxString::FromUTF8(text);

	// ^^^ Check Happens Here ^^^

	m_richTextCtrlRight->SetValue(textFromLeft);
}

   void MyFrame::OnButton2Click(wxCommandEvent& event)
   {
       wxLogMessage("Yakinda Geliyor!");
   }

   void MyFrame::OnButton3Click(wxCommandEvent& event)
   {
       wxLogMessage("Yakinda Geliyor!");
   }
