package DJKeygoe;


import javax.swing.*;


import javax.swing.table.DefaultTableModel;

import javax.swing.JFrame;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.border.BevelBorder;

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

public class NewJDialog extends javax.swing.JDialog implements WindowListener,ActionListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static DJAcsAPIDef 	g_DJApi 	= new DJAcsAPIDef();
	public static Global 		GlobalVar 	= new Global();
	public static NewJDialog 	inst = null;

	private MyTable 			jList_Count;
	private MyTable 			jList_Main;
	private MyTable 			jList_Pcm;
	
	private DefaultTableModel tableModelCount; //for add row to JTable
	private DefaultTableModel tableModelMain;
	private DefaultTableModel tableModelPcm;
	
	private JCheckBox 		jCheckBox_DebugOn;
	private JLabel 			jLabel5;
	private JButton 		jButton_Exit;
	private JButton 		jButton_ReOpen;
	private JButton 		jButton_PreForRem;
	private JRadioButton 	jRadioButton_MostFirst;
	private JRadioButton 	jRadioButton_SameMod;
	private JRadioButton 	jRadioButton_Fix;
	private JRadioButton 	jRadioButton_32;
	private JRadioButton 	jRadioButton_31;
	private JRadioButton 	jRadioButton_30;
	private JLabel 			jLabel4;
	private JTextField 		jEditorPane_ModID;
	private JCheckBox 		jCheckBox_ModID;
	private JTextField 		jEditorPane_VocPath;
	private JTextField 		jEditorPane_ServerPort;
	private JTextField 		jEditorPane_ServerIP;
	private JLabel 			jLabel3;
	private JLabel 			jLabel2;
	private JLabel 			jLabel1;
	private JPanel 			jPanel_Config;
	
	private JScrollPane		scrollCount;
	private JScrollPane		scrollMain;	
	private JScrollPane		scrollPcm;  
	
	private byte g_8AppID = 1; 
	
	private volatile int  g_NumOfListBoxMsg = 0;
	
	private DefaultListModel<String> listBoxDim = new DefaultListModel<String>();
	
	private JList<String> 	jList_MsgBox = new JList<String>(listBoxDim);
	
	JScrollPane scrlpane = null;
	/**
	* Auto-generated main method to display this JDialog
	*/
	public void InitSystem(){ 
		
		GlobalVar.InitCmdParamData_CASData();
		GlobalVar.InitGlobalObjectArr();
		
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
	
	public static void main(String[] args) {
		JFrame frame = new JFrame();
		inst = new NewJDialog(frame);
		inst.setVisible(true);
		
		inst.InitSystem(); 
	}
	
	public NewJDialog(JFrame frame) {
		super(frame);
		getContentPane().setLayout(null);
		initGUI();
		
		this.addWindowListener((WindowListener)this);
	}
	
	public void actionPerformed(ActionEvent e){ //Exit
		NewJDialog.inst.dispose();
	}
	
	private void initGUI() {
		try {
			{
				this.setTitle("Donjin Keygoe Bank Demo System");
				{
					tableModelCount = new DefaultTableModel(new Object[][]{}, new String[] {"ID", "ModID", "Pcm/Open",
							"Trk/Open", "Voc/Open", "VocFree", "ErrFlag", "RemoveState"});
					
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
					tableModelMain = new DefaultTableModel(new Object[][]{}, new String[] {"ID", "Mod,Ch", "Type",
							"LineState", "State", "Called", "Calling", "DTMF", "VocInfo"});
					
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
					tableModelPcm = new DefaultTableModel(new Object[][]{}, new String[] {"PcmID", "Type", "Alarm Value",
							"Sig Detect", "Frame Sync", "Remote Alarm"});
					
					jList_Pcm = new MyTable(tableModelPcm);
					
					jList_Pcm.getTableHeader().setPreferredSize(new Dimension(0,17)); 					
					jList_Pcm.setShowHorizontalLines(false);
					jList_Pcm.setShowVerticalLines(false);
					jList_Pcm.getTableHeader().setFont(new Font("Dialog", Font.PLAIN, 13));
					jList_Pcm.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
					jList_Pcm.setBounds(0, 547, 578, 164);
					
					getContentPane().add(jList_Pcm);
					
					scrollPcm = new JScrollPane(jList_Pcm);  
					scrollPcm.setBounds(0, 547, 578, 164);  
					scrollPcm.setBackground(Color.white);
					scrollPcm.getViewport().setBackground(Color.white);
					
			        add(scrollPcm);
				}
				{
					getContentPane().add(jList_MsgBox);
					jList_MsgBox.setBorder(BorderFactory.createTitledBorder(""));
					jList_MsgBox.setBounds(584, 0, 277, 432);
					
					jList_MsgBox.setFixedCellHeight(13); 
					jList_MsgBox.setFixedCellWidth(500);
					
					scrlpane = new JScrollPane(jList_MsgBox);
					scrlpane.setBounds(584, 0, 277, 432);
					add(scrlpane); 
				}
				{
					jPanel_Config = new JPanel();
					getContentPane().add(jPanel_Config);
					jPanel_Config.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
					jPanel_Config.setLayout(null);
					jPanel_Config.setBounds(584, 438, 277, 244);
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
						jLabel2.setBounds(104, 51, 42, 15);
					}
					{
						jLabel3 = new JLabel();
						jPanel_Config.add(jLabel3);
						jLabel3.setText("Voc Path:");
						jLabel3.setBounds(68, 78, 86, 15);
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
						jEditorPane_ServerPort.setBounds(146, 50, 123, 19);
					}
					{
						jEditorPane_VocPath = new JTextField();
						jPanel_Config.add(jEditorPane_VocPath);
						jEditorPane_VocPath.setText("");
						jEditorPane_VocPath.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
						jEditorPane_VocPath.setBounds(146, 77, 123, 19);
					}
					{
						jLabel5 = new JLabel();
						jPanel_Config.add(jLabel5);
						jLabel5.setText("Voice Search Rule:");
						jLabel5.setBounds(14, 163, 113, 15);
					}
					{
						jCheckBox_ModID = new JCheckBox();
						jPanel_Config.add(jCheckBox_ModID);
						jCheckBox_ModID.setText("Part Work, Module ID:");
						jCheckBox_ModID.setBounds(14, 220, 163, 19);
					}
					{
						jEditorPane_ModID = new JTextField();
						jPanel_Config.add(jEditorPane_ModID);
						jEditorPane_ModID.setText("");
						jEditorPane_ModID.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
						jEditorPane_ModID.setBounds(182, 220, 86, 19);
					}
					{
						jLabel4 = new JLabel();
						jPanel_Config.add(jLabel4);
						jLabel4.setText("Disp Channel Per PCM:");
						jLabel4.setBounds(14, 111, 154, 15);
					}
					{
						jRadioButton_30 = new JRadioButton();
						jPanel_Config.add(jRadioButton_30);
						jRadioButton_30.setText("30");
						jRadioButton_30.setBounds(26, 133, 55, 19);
					}
					{
						jRadioButton_31 = new JRadioButton();
						jPanel_Config.add(jRadioButton_31);
						jRadioButton_31.setText("31");
						jRadioButton_31.setBounds(80, 133, 50, 19);
					}
					{
						jRadioButton_32 = new JRadioButton();
						jPanel_Config.add(jRadioButton_32);
						jRadioButton_32.setText("32");
						jRadioButton_32.setBounds(141, 133, 60, 19);
					}
					{
						jRadioButton_Fix = new JRadioButton();
						jPanel_Config.add(jRadioButton_Fix);
						jRadioButton_Fix.setText("Fix");
						jRadioButton_Fix.setBounds(26, 184, 50, 19);
					}
					{
						jRadioButton_SameMod = new JRadioButton();
						jPanel_Config.add(jRadioButton_SameMod);
						jRadioButton_SameMod.setText("Same Mod");
						jRadioButton_SameMod.setBounds(81, 184, 90, 19);
					}
					{
						jRadioButton_MostFirst = new JRadioButton();
						jPanel_Config.add(jRadioButton_MostFirst);
						jRadioButton_MostFirst.setText("Most First");
						jRadioButton_MostFirst.setBounds(176, 184, 96, 19);
					}
				}
				{
					jButton_PreForRem = new JButton();
					getContentPane().add(jButton_PreForRem);
					jButton_PreForRem.setText("Prepare For Remove");
					jButton_PreForRem.setBounds(394, 121, 154, 22);
					
					jButton_PreForRem.addActionListener(new ActionListener()
			        {
			            public void actionPerformed(ActionEvent e)
			            {
			            	GlobalVar.Remove_OneDsp();
			            }
			        });
					
				}
				{
					jButton_ReOpen = new JButton();
					getContentPane().add(jButton_ReOpen);
					jButton_ReOpen.setText("ReOpen");
					jButton_ReOpen.setMaximumSize(new java.awt.Dimension(0,0));
					jButton_ReOpen.setBounds(603, 688, 91, 22);
					
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
					jButton_Exit.setBounds(759, 688, 91, 22);
					
					jButton_Exit.addActionListener((ActionListener) this);
				}
			}
			
			setSize(869, 742);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * @param strMsg
	 */
	public void ListBox_AddMsg(String strDisplay){
		if (g_NumOfListBoxMsg % 10000 == 0){ 
			//listBoxDim.addElement(g_NumOfListBoxMsg + " " + strDisplay);
				listBoxDim.clear();
		}
		g_NumOfListBoxMsg++;
		listBoxDim.addElement(g_NumOfListBoxMsg + " " + strDisplay);
	}
	
	public void InitTextBox(){ //
		try{
			String strIp = new String(GlobalVar.cfg_ServerID.m_s8ServerIp);
			jEditorPane_ServerIP.setText(strIp);
		
			String strPort = Integer.toString(GlobalVar.cfg_ServerID.m_u32ServerPort);
			jEditorPane_ServerPort.setText(strPort);
			
			jEditorPane_VocPath.setText(GlobalVar.cfg_VocPath);
			
			if (GlobalVar.cfg_iDispChnl == 30){
				jRadioButton_30.setSelected(true);
			} else if (GlobalVar.cfg_iDispChnl == 31){
				jRadioButton_31.setSelected(true);
			} else if (GlobalVar.cfg_iDispChnl == 32){
				jRadioButton_32.setSelected(true);
			}
			
			if (GlobalVar.cfg_iVoiceRule == 0){
				jRadioButton_Fix.setSelected(true);
			} else if (GlobalVar.cfg_iVoiceRule == 1){
				jRadioButton_SameMod.setSelected(true);
			} else {
				jRadioButton_MostFirst.setSelected(true);
			}
			
			if (GlobalVar.cfg_s32DebugOn == 0){
				jCheckBox_DebugOn.setSelected(false);
			} else {
				jCheckBox_DebugOn.setSelected(true);
			}
			
			String strModID = Integer.toString(GlobalVar.cfg_iPartWorkModuleID);
			jEditorPane_ModID.setText(strModID);
			
			if (GlobalVar.cfg_iPartWork == 0){
				jCheckBox_ModID.setSelected(false);
			} else {
				jCheckBox_ModID.setSelected(true);
			}
		}catch(Exception ee){
		}
	}
	
	public void FetchTextBox(){
		String strIp = jEditorPane_ServerIP.getText(); 
		GlobalVar.CharsToByte(GlobalVar.cfg_ServerID.m_s8ServerIp, strIp.toCharArray(), strIp.length());
		
		String strPort = jEditorPane_ServerPort.getText();
		GlobalVar.cfg_ServerID.m_u32ServerPort = Integer.parseInt(strPort); 
		
		GlobalVar.cfg_VocPath = jEditorPane_VocPath.getText();
		
		if (jRadioButton_30.isSelected() == true){
			GlobalVar.cfg_iDispChnl = 30;
		}
		if (jRadioButton_31.isSelected() == true){
			GlobalVar.cfg_iDispChnl = 31;
		}
		if (jRadioButton_32.isSelected() == true){
			GlobalVar.cfg_iDispChnl = 32;
		}
		
		if (jRadioButton_Fix.isSelected() == true){
			GlobalVar.cfg_iVoiceRule = 0;
		}
		if (jRadioButton_SameMod.isSelected() == true){
			GlobalVar.cfg_iVoiceRule = 1;
		}
		if (jRadioButton_MostFirst.isSelected() == true){
			GlobalVar.cfg_iVoiceRule = 2;
		}
		
		if (jCheckBox_ModID.isSelected() == false){
			GlobalVar.cfg_iPartWork = 0;
		} else {
			GlobalVar.cfg_iPartWork = 1;
		}
		
		String strModID = jEditorPane_ModID.getText();
		GlobalVar.cfg_iPartWorkModuleID = Integer.parseInt(strModID);
		
		if (jCheckBox_DebugOn.isSelected() == false){
			GlobalVar.cfg_s32DebugOn = 0;
		} else {
			GlobalVar.cfg_s32DebugOn = 1;
		}	
	}
	
	public void AddRowToCount(int nNumOfRow){
		if (tableModelCount.getRowCount() == 0){
			tableModelCount.insertRow(tableModelCount.getRowCount(), new Object[] {"Total"});
		}
		for (int i=tableModelCount.getRowCount(); i<nNumOfRow+1; i++){
			tableModelCount.insertRow(i, new Object[] {Integer.toString(i)});
		}
	}
	
	public void AddRowToMain(int nNumOfRow){
		for (int i = tableModelMain.getRowCount(); i < nNumOfRow; i++){
			int iDispRow = GlobalVar.CalDispRow (i);
			if (iDispRow < 0){
				continue;
			}
			tableModelMain.insertRow(i, new Object[] {Integer.toString(iDispRow)});
		}
	}
	
	public void AddRowToPcm(int nNumOfRow){
		for (int i = tableModelPcm.getRowCount(); i < nNumOfRow; i++){
			tableModelPcm.insertRow(i, new Object[] {Integer.toString(i)});
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

	@Override
	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		// TODO Auto-generated method stub
		FetchTextBox();
    	GlobalVar.WriteToConfig(); 
    	NewJDialog.g_DJApi.XMS_acsCloseStream(GlobalVar.g_acsHandle, null);
    	System.exit(0);
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		FetchTextBox();
    	GlobalVar.WriteToConfig(); 
    	NewJDialog.g_DJApi.XMS_acsCloseStream(GlobalVar.g_acsHandle, null);
    	System.exit(0);
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

/*	public int GetSelectedRow() {
		// TODO Auto-generated method stub
		return jList_Count.getSelectedRow();
	}*/

	public int GetSelectedRow() {
		// TODO Auto-generated method stub
		return jList_Count.getSelectedRow();
	}
}
