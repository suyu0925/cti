package DJKeygoe;


import java.awt.BorderLayout;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.BorderFactory;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.border.BevelBorder;
import javax.swing.table.DefaultTableModel;

import java.awt.event.*; 
import java.util.Timer;
import java.util.TimerTask;



class MyTable extends JTable{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public MyTable(DefaultTableModel tableModelCount) {
		// TODO Auto-generated constructor stub
    	super(tableModelCount);
	}

	public boolean isCellEditable(int row,int column){
            return false;
    }
  }


/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
*/
public class NewJDialog extends javax.swing.JDialog implements WindowListener,ActionListener{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static DJAcsAPIDef 	g_DJApi 	= new DJAcsAPIDef();
	public static Global 		GlobalVar 	= new Global();
	public static NewJDialog 	Dialog 		= null;

	private MyTable jList_Pcm;
	private MyTable jList_Count;
	private MyTable jList_User;
	private MyTable jList_Main;
	
	private DefaultTableModel tableModelCount;
	private DefaultTableModel tableModelMain;
	private DefaultTableModel tableModelPcm;
	private DefaultTableModel tabelModelUser;
	
	private JScrollPane		scrollCount;
	private JScrollPane		scrollMain;	
	private JScrollPane		scrollPcm;  
	private JScrollPane		scrollUser;
	
	private JButton jButton_PreForRem;
	private JButton jButton_Exit;
	private JButton jButton_ReOpen;
	private JButton jButton_Simulate;

	private JCheckBox jCheckBox_DebugOn;
	private JCheckBox jCheckBox_ModID;
	
	private JRadioButton jRadioButton_Dtmf;
	private JRadioButton jRadioButton_Loop;
	private JRadioButton jRadioButton_Seq;
	
	private JTextField jEditorPane_CalledNum;
	private JTextField jEditorPane_CalledLen;
	private JTextField jEditorPane_ServerPort;
	private JTextField jEditorPane_ServerIP;
	private JTextField jEditorPane_Calling;
	private JTextField jEditorPane_ModID;
	
	private JLabel jLabel3;
	private JLabel jLabel2;
	private JLabel jLabel1;
	private JLabel jLabel4;
	private JLabel jLabel5;
	
	private JPanel jPanel_Config;
	
	private DefaultListModel<String> listBoxDim = new DefaultListModel<String>();
	
	private JList<String> 	jList_MsgBox = new JList<String>(listBoxDim);
	
	JScrollPane scrlpane = null;
	
	private byte g_8AppID = 2; 
	
	private int g_NumOfListBoxMsg = 0;
	
	public static void Strcpy(byte Dest[], byte Sour[], int nLen){
		for (int i = 0; i < nLen; i++){
			Dest[i] = Sour[i];
		}
	}
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				JFrame frame = new JFrame();
				Dialog = new NewJDialog(frame);
				Dialog.setVisible(true);
				
				Dialog.InitStstem();
			}
		});
	
	}
	
	public void SetGtd_AnalogTrunk(DeviceID_t DevId){
		GlobalVar.g_cmdVoc.m_u8GtdCtrlValid = 1 ; //Enable GTD
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;//Enable Gtd channel
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8MR2FEnable = 1;
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8MR2BEnable = 1;
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;
		
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDID[0] = (byte)'G';
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDID[1] = (byte)'H';
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDID[2] = (byte)'I';
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDID[3] = (byte)'J';
		GlobalVar.g_cmdVoc.m_VocGtdControl.m_u8GTDID[4] = (byte)'K';

		short u16ParamType = XMS_VOC_PARAM_TYPE.VOC_PARAM_UNIPARAM;
		
		int r = g_DJApi.XMS_ctsSetParam(GlobalVar.g_acsHandle,DevId,u16ParamType, (short)0, GlobalVar.g_cmdVoc);
		
		String Str = "Set GTD ret = " + Integer.toString(r);
		ListBox_AddMsg (Str);
	}
	
	public void LoopCall(){
		Timer timer = new Timer(); 

        timer.schedule(new TimerTask() {
           @Override
           public void run() {
        	   SimulateCallOut();
        }
     }, 0, 100);
	}
	
	public void	SimulateCallOut(){ //Call Out

	    
		DeviceID_t FreeTrkDeviceID = GlobalVar.SearchOneFreeTrunk(GlobalVar.cfg_SimCalledNum.getBytes());
		
		if (FreeTrkDeviceID != null){
			GlobalVar.cfg_SimCalledNum = jEditorPane_CalledNum.getText();
			GlobalVar.cfg_CallingNum = jEditorPane_Calling.getText();
			
			TRUNK_STRUCT OneTrk = GlobalVar.GetTrunkStructByDevice(FreeTrkDeviceID.m_s8ModuleID, FreeTrkDeviceID.m_s16ChannelID);
			
			if (FreeTrkDeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
					&& FreeTrkDeviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
				DeviceID_t FreeVocDeviceID = GlobalVar.SearchOneFreeVoice(OneTrk);
				if (FreeVocDeviceID != null){
					VOICE_STRUCT OneVoc = GlobalVar.GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID);
					
					GlobalVar.My_DualLink(FreeTrkDeviceID, FreeVocDeviceID);
					
					OneVoc.UsedDevID = FreeTrkDeviceID;
					OneTrk.VocDevID = FreeVocDeviceID;
					
					SetGtd_AnalogTrunk(FreeVocDeviceID);
				} else {
					ListBox_AddMsg("No VoiceDevice is Free!,SearchOneFreeVoice Failed!");
					return ;
				}
			}
			
			byte s8Calling[] = new byte[GlobalVar.cfg_CallingNum.length()+1];
			byte s8Called[] = new byte[GlobalVar.cfg_SimCalledNum.length() + 1];
			
			Global.CharsToByte(s8Calling, GlobalVar.cfg_CallingNum.toCharArray(), GlobalVar.cfg_CallingNum.length());
			Global.CharsToByte(s8Called, GlobalVar.cfg_SimCalledNum.toCharArray(), GlobalVar.cfg_SimCalledNum.length());
			
			int nRet = g_DJApi.XMS_ctsMakeCallOut(GlobalVar.g_acsHandle, FreeTrkDeviceID, s8Calling, s8Called, null);
			
			if (nRet > 0){
				// call out OK
				GlobalVar.DrawMain_LinkDev (OneTrk);

				NewJDialog.Strcpy ( OneTrk.CallerCode, GlobalVar.cfg_CallingNum.getBytes(), GlobalVar.cfg_CallingNum.length());
				NewJDialog.Strcpy ( OneTrk.CalleeCode, GlobalVar.cfg_SimCalledNum.getBytes(), GlobalVar.cfg_SimCalledNum.length());
				GlobalVar.DrawMain_CallInfo ( OneTrk );

				GlobalVar.Change_State ( OneTrk, TRUNK_STATE.TRK_SIM_CALLOUT );
			}
			else{
				ListBox_AddMsg("XMS_ctsMakeCallOut() FAIL! ret = " + Integer.toString(nRet));
			}
		}
	}
	
	public void InitStstem(){

		GlobalVar.InitCmdParamData_CASData();
		GlobalVar.InitObjectArr();
		
		PrivateData_t priData = new PrivateData_t();
		priData.m_u32DataSize = 0;
		
		GlobalVar.ReadFromConfig();
	
		if (Cas_Commom_Cfg.CAS_Common_Cfg_ReadCfg(GlobalVar.g_Param_CAS) != 0){
			System.out.println("CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!");
		}
		
		if (Analog_Common_Code.Analog_Common_Cfg_ReadCfg(GlobalVar.g_Param_Analog) != 0){
			System.out.println("Analog_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI\" Error!");
		}
	
		InitTextBox();
		
		GlobalVar.g_acsHandle = g_DJApi.XMS_acsOpenStream(GlobalVar.g_acsHandle, 
				GlobalVar.cfg_ServerID, g_8AppID, 32, 32, GlobalVar.cfg_s32DebugOn, priData);

		if (GlobalVar.g_acsHandle < 0){
			ListBox_AddMsg("Open Stream Fail");;
		}
		
		EsrFunc esr = new EsrFunc();
		g_DJApi.XMS_acsSetESR(GlobalVar.g_acsHandle, esr, 0, 1);
		
		g_DJApi.XMS_acsGetDeviceList(GlobalVar.g_acsHandle, priData);
	}
	
	public NewJDialog(JFrame frame) {
		super(frame);
		getContentPane().setLayout(null);
		this.setTitle("Donjin Keygoe Dial System");
		
		{
			tableModelCount = new DefaultTableModel(new Object[][]{}, new String[] {"ID", "ModID", "Pcm/Open",
					"Trk/Open", "Voc/Open", "VocFree", "User/Open", "ErrFlag", "RemoveState"});
			
			jList_Count = new MyTable(tableModelCount);
			
			jList_Count.getTableHeader().setPreferredSize(new Dimension(0,17)); 
			jList_Count.setShowHorizontalLines(false);
			jList_Count.setShowVerticalLines(false);
			jList_Count.getTableHeader().setFont(new Font("Dialog", Font.PLAIN, 13));
			jList_Count.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
			jList_Count.setBounds(0, 0, 578, 120);
			
			getContentPane().add(jList_Count, BorderLayout.CENTER);
			
			scrollCount = new JScrollPane(jList_Count);  
			scrollCount.setBounds(0, 0, 578, 120);  
			scrollCount.getViewport().setBackground(Color.white);
	        add(scrollCount);
		}
		{
			jButton_PreForRem = new JButton();
			getContentPane().add(jButton_PreForRem);
			jButton_PreForRem.setText("Prepare For Remove");
			jButton_PreForRem.setBounds(407, 122, 154, 22);
			
			jButton_PreForRem.addActionListener(new ActionListener()
	        {
	            public void actionPerformed(ActionEvent e)
	            {
	            	GlobalVar.Remove_OneDsp();
	            }
	        });
			
		}
		{
			tableModelMain = new DefaultTableModel(new Object[][]{}, new String[] {"ID", "Mod,Ch", "Type",
					"LineState", "State", "Called", "Calling", "LinkDev", "FailReason"});
			
			jList_Main = new MyTable(tableModelMain);
			
			jList_Main.getTableHeader().setPreferredSize(new Dimension(0,17)); 
			jList_Main.setShowHorizontalLines(false); 
			jList_Main.setShowVerticalLines(false); 
			jList_Main.getTableHeader().setFont(new Font("Dialog", Font.PLAIN, 13));
			jList_Main.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
			jList_Main.setBounds(0, 145, 578, 400);
			
			getContentPane().add(jList_Main);
	
			scrollMain = new JScrollPane(jList_Main);  
			scrollMain.setBounds(0, 145, 578, 400);  
			scrollMain.getViewport().setBackground(Color.white);
	        
	        add(scrollMain);
		}
		{
			tabelModelUser = new DefaultTableModel(new Object[][]{}, new String[] {"ID", "Mod,Ch", "Type",
					"LineState", "State", "DTMF", "VocInfo", "LinkDev"});
			
			jList_User = new MyTable(tabelModelUser);
			
			jList_User.getTableHeader().setPreferredSize(new Dimension(0,17)); 
			jList_User.setShowHorizontalLines(false);
			jList_User.setShowVerticalLines(false);
			jList_User.getTableHeader().setFont(new Font("Dialog", Font.PLAIN, 13));
			jList_User.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
			jList_User.setBounds(0, 550, 578, 161);
			
			getContentPane().add(jList_User);
	
			scrollUser = new JScrollPane(jList_User);  
			scrollUser.setBounds(0, 550, 578, 161);  
			scrollUser.getViewport().setBackground(Color.white);
	        
	        add(scrollUser);
		}
		{
			getContentPane().add(jList_MsgBox);
			jList_MsgBox.setBorder(BorderFactory.createTitledBorder(""));
			jList_MsgBox.setBounds(584, 0, 277, 432);
			
			
			jList_MsgBox.setFixedCellHeight(13); 
			jList_MsgBox.setFixedCellWidth(500); 
			
			scrlpane = new JScrollPane(jList_MsgBox);
			scrlpane.setBounds(581, 0, 277, 314);
			add(scrlpane); 
		}
		{
			tableModelPcm = new DefaultTableModel(new Object[][]{}, new String[] {"PcmID", "Type", "Alarm Value",
					"Sig Detect", "Frame Sync", "Remote Alarm"});
			
			jList_Pcm = new MyTable(tableModelPcm);
			
			jList_Pcm.getTableHeader().setPreferredSize(new Dimension(0,17)); 
			jList_Pcm.setShowHorizontalLines(false);
			jList_Pcm.setShowVerticalLines(false);
			jList_Pcm.getTableHeader().setFont(new Font("Dialog", Font.PLAIN, 13));
			jList_Pcm.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
			jList_Pcm.setBounds(582, 317, 277, 164);
			
			getContentPane().add(jList_Pcm);
			
			scrollPcm = new JScrollPane(jList_Pcm);  
			scrollPcm.setBounds(582, 317, 277, 164);  
			scrollPcm.setBackground(Color.white);
			scrollPcm.getViewport().setBackground(Color.white);
			
	        add(scrollPcm);
		}
		{
			jButton_ReOpen = new JButton();
			getContentPane().add(jButton_ReOpen);
			jButton_ReOpen.setText("ReOpen");
			jButton_ReOpen.setMaximumSize(new java.awt.Dimension(0,0));
			jButton_ReOpen.setBounds(590, 687, 91, 22);
			
			jButton_ReOpen.addActionListener(new ActionListener()
	        {
	            public void actionPerformed(ActionEvent e)
	            {
	            	GlobalVar.ReOpen_AllDevice();
	            }
	        });
			
		}
		{
			jButton_Exit = new JButton();
			getContentPane().add(jButton_Exit);
			jButton_Exit.setText("Exit");
			jButton_Exit.setBounds(759, 687, 91, 22);
			
			jButton_Exit.addActionListener((ActionListener) this);
		}
		{
			jPanel_Config = new JPanel();
			getContentPane().add(jPanel_Config);
			jPanel_Config.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
			jPanel_Config.setLayout(null);
			jPanel_Config.setBounds(582, 484, 277, 199);
			{
				jCheckBox_DebugOn = new JCheckBox();
				jPanel_Config.add(jCheckBox_DebugOn);
				jCheckBox_DebugOn.setText("Debug Mode On");
				jCheckBox_DebugOn.setBounds(12, 2, 182, 20);
			}
			{
				jLabel1 = new JLabel();
				jPanel_Config.add(jLabel1);
				jLabel1.setText("Server IP Addr:");
				jLabel1.setBounds(45, 25, 94, 15);
			}
			{
				jLabel2 = new JLabel();
				jPanel_Config.add(jLabel2);
				jLabel2.setText("Port:");
				jLabel2.setBounds(104, 46, 42, 15);
			}
			{
				jLabel3 = new JLabel();
				jPanel_Config.add(jLabel3);
				jLabel3.setText("Called Len:");
				jLabel3.setBounds(68, 68, 86, 15);
			}
			{
				jLabel4 = new JLabel();
				jPanel_Config.add(jLabel4);
				jLabel4.setText("Calling Num:");
				jLabel4.setBounds(62, 90, 87, 15);
			}
			{
				jEditorPane_ServerIP = new JTextField();
				jPanel_Config.add(jEditorPane_ServerIP);
				jEditorPane_ServerIP.setText("");
				jEditorPane_ServerIP.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_ServerIP.setBounds(146, 23, 123, 19);
			}
			{
				jEditorPane_ServerPort = new JTextField();
				jPanel_Config.add(jEditorPane_ServerPort);
				jEditorPane_ServerPort.setText("");
				jEditorPane_ServerPort.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_ServerPort.setBounds(146, 45, 123, 19);
			}
			{
				jEditorPane_CalledLen = new JTextField();
				jPanel_Config.add(jEditorPane_CalledLen);
				jEditorPane_CalledLen.setText("");
				jEditorPane_CalledLen.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_CalledLen.setBounds(146, 67, 123, 19);
			}
			{ 
				jEditorPane_Calling = new JTextField();
				jPanel_Config.add(jEditorPane_Calling);
				jEditorPane_Calling.setText("");
				jEditorPane_Calling.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_Calling.setBounds(146, 89, 123, 19);
			}
			{
				jLabel5 = new JLabel();
				jPanel_Config.add(jLabel5);
				jLabel5.setText("Call Out Rule:");
				jLabel5.setBounds(14, 109, 84, 15);
			}
			{
				jRadioButton_Seq = new JRadioButton();
				jPanel_Config.add(jRadioButton_Seq);
				jRadioButton_Seq.setText("Sequence");
				jRadioButton_Seq.setBounds(24, 123, 85, 19);
			}
			{
				jRadioButton_Loop = new JRadioButton();
				jPanel_Config.add(jRadioButton_Loop);
				jRadioButton_Loop.setText("Loop");
				jRadioButton_Loop.setBounds(111, 123, 56, 19);
			}
			{
				jRadioButton_Dtmf = new JRadioButton();
				jPanel_Config.add(jRadioButton_Dtmf);
				jRadioButton_Dtmf.setText("Dtmf Tail 3");
				jRadioButton_Dtmf.setBounds(170, 123, 99, 19);
			}
			{
				jButton_Simulate = new JButton();
				jPanel_Config.add(jButton_Simulate);
				jButton_Simulate.setText("Simulate");
				jButton_Simulate.setBounds(24, 148, 85, 22);
				
				jButton_Simulate.addActionListener(new ActionListener()
		        {
		            public void actionPerformed(ActionEvent e)
		            {
		            	//LoopCall();
		            	SimulateCallOut();
		            }
		        });
			}
			{
				jEditorPane_CalledNum = new JTextField();
				jPanel_Config.add(jEditorPane_CalledNum);
				jEditorPane_CalledNum.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_CalledNum.setBounds(146, 149, 123, 19);
			}
			{
				jCheckBox_ModID = new JCheckBox();
				jPanel_Config.add(jCheckBox_ModID);
				jCheckBox_ModID.setText("Part Work, Module ID:");
				jCheckBox_ModID.setBounds(14, 176, 163, 19);
			}
			{
				jEditorPane_ModID = new JTextField();
				jPanel_Config.add(jEditorPane_ModID);
				jEditorPane_ModID.setText("");
				jEditorPane_ModID.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
				jEditorPane_ModID.setBounds(182, 174, 86, 19);
			}
		}
		
		initGUI();
  
		this.addWindowListener((WindowListener)this);
	} 
	
	public void actionPerformed(ActionEvent e){ //Exit
		NewJDialog.Dialog.dispose();
	}
	
	private void initGUI() {
		try {
			setSize(868, 743);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void	InitTextBox(){
		String strIp = new String(GlobalVar.cfg_ServerID.m_s8ServerIp);
		jEditorPane_ServerIP.setText(strIp);
	
		String strPort = Integer.toString(GlobalVar.cfg_ServerID.m_u32ServerPort);
		jEditorPane_ServerPort.setText(strPort);
		
		String strCalledLen = Integer.toString(GlobalVar.cfg_iCalledLen);
		jEditorPane_CalledLen.setText(strCalledLen);
		
		jEditorPane_Calling.setText(GlobalVar.cfg_CallingNum);
		
		if (GlobalVar.cfg_iCallOutRule == 0){
			jRadioButton_Seq.setSelected(true);
		} else if (GlobalVar.cfg_iCallOutRule == 1){
			jRadioButton_Loop.setSelected(true);
		} else if (GlobalVar.cfg_iCallOutRule == 2){
			jRadioButton_Dtmf.setSelected(true);
		}
		
		jEditorPane_CalledNum.setText(GlobalVar.cfg_SimCalledNum);
		
		if (GlobalVar.cfg_iPartWork == 0){
			jCheckBox_ModID.setSelected(false);
		} else {
			jCheckBox_ModID.setSelected(true);
		}
	
		String strModID = Integer.toString(GlobalVar.cfg_iPartWorkModuleID);
		jEditorPane_ModID.setText(strModID);
		
		if (GlobalVar.cfg_s32DebugOn == 0){
			jCheckBox_DebugOn.setSelected(false);
		} else {
			jCheckBox_DebugOn.setSelected(true);
		}
	}
	
	public void FetchTextBox(){
		String strIp = jEditorPane_ServerIP.getText(); 
		Global.CharsToByte(GlobalVar.cfg_ServerID.m_s8ServerIp, strIp.toCharArray(), strIp.length());
		
		String strPort = jEditorPane_ServerPort.getText();
		GlobalVar.cfg_ServerID.m_u32ServerPort = Integer.parseInt(strPort);
		
		String strCalledLen = jEditorPane_CalledLen.getText();
		GlobalVar.cfg_iCalledLen = Integer.parseInt(strCalledLen);
		
		GlobalVar.cfg_CallingNum = jEditorPane_Calling.getText();
		
		if (jRadioButton_Seq.isSelected() == true){
			GlobalVar.cfg_iCallOutRule = 0;
		} else if (jRadioButton_Loop.isSelected() == true){
			GlobalVar.cfg_iCallOutRule = 1;
		} else if (jRadioButton_Dtmf.isSelected() == true){
			GlobalVar.cfg_iCallOutRule = 2;
		}
		
		GlobalVar.cfg_SimCalledNum = jEditorPane_CalledNum.getText();
		
		if (jCheckBox_DebugOn.isSelected() == true){
			GlobalVar.cfg_s32DebugOn = 1;
		} else{
			GlobalVar.cfg_s32DebugOn = 0;
		}
	
		String strModID = jEditorPane_ModID.getText();
		GlobalVar.cfg_iPartWorkModuleID = Integer.parseInt(strModID);
		
		if (jCheckBox_ModID.isSelected() == true){
			GlobalVar.cfg_iPartWork = 1;
		} else {
			GlobalVar.cfg_iPartWork = 0;
		}
	}
	
	/**
	 * @param strMsg
	 */
	public void ListBox_AddMsg(String strDisplay){
		if (g_NumOfListBoxMsg % 10000 == 0){
			listBoxDim.clear();
			//listBoxDim.addElement(g_NumOfListBoxMsg + " " + strDisplay);
		}
		g_NumOfListBoxMsg++;
		listBoxDim.addElement(g_NumOfListBoxMsg + " " + strDisplay);
	}
	
	public void AddRowToCount(int nNumOfRow){
		if (tableModelCount.getRowCount() == 0){
			tableModelCount.insertRow(tableModelCount.getRowCount(), new Object[] {"Total"});
		}
		for (int i = tableModelCount.getRowCount(); i < nNumOfRow+1; i++){
			tableModelCount.insertRow(i, new Object[] {Integer.toString(i)});
		}
	}
	
	public void AddRowToMain(int nNumOfRow){
		for (int i=tableModelMain.getRowCount(); i<nNumOfRow; i++){
			tableModelMain.insertRow(i, new Object[] {Integer.toString(i)});
		}
	}
	
	public void AddRowToPcm(int nNumOfRow){
		for (int i=tableModelPcm.getRowCount(); i<nNumOfRow; i++){
			tableModelPcm.insertRow(i, new Object[] {Integer.toString(i)});
		}
	}
	
	public void AddRowToUser(int nNumOfRow){
		for (int i = tabelModelUser.getRowCount(); i < nNumOfRow; i++){
			tabelModelUser.insertRow(i, new Object[]{Integer.toString(i)});
		}
	}
	
	void DeleteCountAllItems(){
		int n = tableModelCount.getRowCount() - 1;
		while(n >= 0){ 
		   tableModelCount.removeRow(n);
		   n--;
		   }
	}
	
	void DeleteMainAllItems(){
		int n = tableModelMain.getRowCount() - 1;
		while(n >= 0){ 
		   tableModelMain.removeRow(n);
		   n--;
		   }
	}
	
	void DeletePcmAllItems(){
		int n = tableModelPcm.getRowCount() - 1;
		while(n >= 0){ 
		   tableModelPcm.removeRow(n);
		   n--;
		   }
	}
	
	void DeleteUserAllItems(){
		int n = tabelModelUser.getRowCount() - 1;
		while(n >= 0){ 
		   tabelModelUser.removeRow(n);
		   n--;
		   }
	}
	
	void DrawCount(int nRow, int nColumn, String Str){
		jList_Count.setValueAt(Str, nRow, nColumn);
	}
	
	void DrawMain(int nRow, int nColumn, String Str){
		jList_Main.setValueAt(Str, nRow, nColumn);
	}
	
	void DrawPcm(int nRow, int nColumn, String Str){
		jList_Pcm.setValueAt(Str, nRow, nColumn);
	}
	
	void DrawUser(int nRow, int nColumn, String Str){
		jList_User.setValueAt(Str, nRow, nColumn);
	}

	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	
	public void windowClosed(WindowEvent arg0) {
		// TODO Auto-generated method stub
		FetchTextBox();
    	GlobalVar.WriteToConfig(); 
    	NewJDialog.g_DJApi.XMS_acsCloseStream(GlobalVar.g_acsHandle, null);
    	System.exit(0);
	}
	
	public void windowClosing(WindowEvent e) {   
		// TODO Auto-generated method stub  
		FetchTextBox();
    	GlobalVar.WriteToConfig(); 
    	NewJDialog.g_DJApi.XMS_acsCloseStream(GlobalVar.g_acsHandle, null);
    	System.exit(0);
	}  

	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
	}

	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	public int GetSelectedRow() {
		// TODO Auto-generated method stub
		return jList_Count.getSelectedRow();
	}

}
