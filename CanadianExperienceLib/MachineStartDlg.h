/**
 * @file MachineStartDlg.h
 * @author Seth Darling
 *
 * Machine Start Frame dialog box
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H

class MachineDrawable;

/**
 * Machine Start Frame dialog box
 */
class MachineStartDlg final : public wxDialog
{
private:
	void OnOK(wxCommandEvent& event);

	/// The pointer to the first machine drawable
	std::shared_ptr<MachineDrawable> mMachineDrawableOne;

	/// The pointer to the second machine drawable
	std::shared_ptr<MachineDrawable> mMachineDrawableTwo;

	/// Start frame for Machine One
	int mMachineOneStart = 0;

	/// Start frame for Machine Two
	int mMachineTwoStart = 0;
public:
	MachineStartDlg(wxWindow *parent, std::shared_ptr<MachineDrawable> machineOne, std::shared_ptr<MachineDrawable> machineTwo);
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H
