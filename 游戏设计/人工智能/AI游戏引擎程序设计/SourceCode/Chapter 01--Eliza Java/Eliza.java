import java.awt.*;
import java.applet.*;

public class Eliza extends Applet {

	
    ElizaChat       cq[];
    ElizaRespLdr    ChatLdr;
    static ElizaConjugate  ChatConj;
    boolean         _started=false;
    Font            _font;
    String          _s;

    public void init() {

        super.init();
        ChatLdr = new ElizaRespLdr();
        ChatConj = new ElizaConjugate();

    	//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(425,313);
		setBackground(new Color(16776960));
		list1 = new java.awt.List(0,false);
		list1.addItem("Hi! I'm Eliza.  Let's talk.");
		add(list1);
		list1.reshape(12,12,395,193);
		list1.setFont(new Font("TimesRoman", Font.BOLD, 14));
		list1.setBackground(new Color(16777215));
		button1 = new java.awt.Button("Depress the Button or depress <Enter> to send to Eliza");
		button1.reshape(48,264,324,26);
		button1.setFont(new Font("Helvetica", Font.PLAIN, 12));
		button1.setForeground(new Color(0));
		add(button1);
		textField1 = new java.awt.TextField();
		textField1.reshape(36,228,348,24);
		textField1.setFont(new Font("TimesRoman", Font.BOLD, 14));
		textField1.setBackground(new Color(16777215));
		add(textField1);
		//}}
        textField1.requestFocus();
    }

    public boolean action(Event event, Object arg)  {
        if (event.id == Event.ACTION_EVENT && event.target == button1) {
                clickedButton1();
                textField1.requestFocus();
                return true;
        }
        if (event.id == Event.ACTION_EVENT && event.target == textField1) {
                clickedButton1();
                textField1.requestFocus();
                return true;
        }
        return super.handleEvent(event);
    }

    public void clickedButton1() {
        parseWords(textField1.getText());
        textField1.setText("");
        textField1.setEditable(true);
        textField1.requestFocus();

    }
    public void parseWords(String s_) {
        int idx=0, idxSpace=0;
        int _length=0;      // actual no of elements in set
        int _maxLength=200;  // capacity of set
        int _w;

        list1.addItem(s_);
        list1.makeVisible(list1.getVisibleIndex()+1);
        s_=s_.toLowerCase()+" ";
        while(s_.indexOf("'")>=0)
            s_=s_.substring(0,s_.indexOf("'"))+s_.substring(s_.indexOf("'")+1,s_.length());

        bigloop: for(_length=0; _length<_maxLength  && idx < s_.length(); _length++){
            // find end of the first token
            idxSpace=s_.indexOf(" ",idx);
            if(idxSpace == -1) idxSpace=s_.length();

           String _resp=null;
           for(int i=0;i<ElizaChat.num_chats && _resp == null;i++) {
               _resp=ChatLdr.cq[i].converse(s_.substring(idx,s_.length()));
               if(_resp != null) {
                   list1.addItem(_resp);
                   list1.makeVisible(list1.getVisibleIndex()+1);
                   break bigloop;
               }
           }
           // eat blanks
           while(s_.length() > ++idxSpace && Character.isSpace(s_.charAt(idxSpace)));
           idx=idxSpace;

           if(idx >= s_.length())   {
                _resp=ChatLdr.cq[ElizaChat.num_chats-1].converse("nokeyfound");
                list1.addItem(_resp);
                list1.makeVisible(list1.getVisibleIndex()+1);
           }
        }
    }
	//{{DECLARE_CONTROLS
	java.awt.List list1;
	java.awt.Button button1;
	java.awt.TextField textField1;
	//}}
}