/**
 * @file MachineStartDlg.cpp
 * @author seth
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include <memory>

#include "MachineStartDlg.h"
#include "MachineDrawable.h"

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param machineOne Machine Drawable One
 * @param machineTwo Machine Drawable Two
 */
MachineStartDlg::MachineStartDlg(wxWindow *parent, std::shared_ptr<MachineDrawable> machineOne, std::shared_ptr<MachineDrawable> machineTwo)
{
	wxXmlResource::Get()->LoadDialog(this, parent, L"StartFrameDlg");

	mMachineDrawableOne = machineOne;
	mMachineDrawableTwo = machineTwo;

	mMachineOneStart = machineOne->GetStartFrame();
	mMachineTwoStart = machineTwo->GetStartFrame();

	Bind(wxEVT_BUTTON, &MachineStartDlg::OnOK, this, wxID_OK);

	auto oneStartCtrl = XRCCTRL(*this, "Machine1StartFrame", wxTextCtrl);
	wxIntegerValidator<int> oneStartValidator(&mMachineOneStart);
	oneStartValidator.SetRange(0, 10000);
	oneStartCtrl->SetValidator(oneStartValidator);

	auto twoStartCtrl = XRCCTRL(*this, "Machine2StartFrame", wxTextCtrl);
	wxIntegerValidator<int> twoStartValidator(&mMachineTwoStart);
	twoStartValidator.SetRange(0, 10000);
	twoStartCtrl->SetValidator(twoStartValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineStartDlg::OnOK(wxCommandEvent &event)
{
	if ( Validate() && TransferDataFromWindow() )
	{
		// Success! Set values in the class
		mMachineDrawableOne->SetStartFrame(mMachineOneStart);
		mMachineDrawableTwo->SetStartFrame(mMachineTwoStart);

		EndModal(wxID_OK);
	}
}
