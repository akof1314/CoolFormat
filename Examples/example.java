package com.kaleo89;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

import com.kaleo89.bizhizhuanhuan.handlewin;
public class testgridbag {
    public static void main(String args[]){
    new gridexam();

}}
class gridexam extends Frame{
    int i;
    boolean xinjian=false;
    GridBagLayout gb;
    GridBagConstraints gbc;
    TextField year,month;
    Label a7,a1,a2,a3,a4,a5,a6,year_label,month_label;
    Button [] btn=new Button[42];
    Button commit,newpost,zhuandao;
    TextArea text;
    Label konge;
    int [] monnum={31,28,31,30,31,30,31,31,30,31,30,31};
    int longnum,endnum,temp;
    int startnum,endnumtemp;
    int yearnow,monthnow;
    int yeara=0,montha=0,daya=0;
    String s;
    Statement sta;
    String url;Connection conn;
    private void setlabel(Label a){
        gb.setConstraints(a, gbc);
        add(a);
    }
    gridexam(){
        addWindowListener(new handlewin());
        gb=new GridBagLayout();
        gbc=new GridBagConstraints();
        
        a7=new Label("星期日");
        a1=new Label("星期一");
        a2=new Label("星期二");a3=new Label("星期三");a4=new Label("星期四");a5=new Label("星期五");a6=new Label("星期六");konge=new Label("           ");
        year_label=new Label("年");month_label=new Label("月");
        year=new TextField("1998",8);month=new TextField("12" ,8);
        zhuandao=new Button("转到");
        this.setLayout(gb);
        gbc.fill=GridBagConstraints.BOTH;
        
        gb.setConstraints(year, gbc);
        add(year);
        
        gb.setConstraints(year_label, gbc);
        add(year_label);
        
        gb.setConstraints(konge, gbc);
        add(konge);
        gb.setConstraints(month, gbc);
        add(month);
        gb.setConstraints(month_label, gbc);
        add(month_label);
        gbc.gridwidth=GridBagConstraints.REMAINDER;
        
        gb.setConstraints(zhuandao, gbc);
        add(zhuandao);
        
        gbc.gridwidth=1;
        setlabel(a7);setlabel(a1);setlabel(a2);setlabel(a3);setlabel(a4);setlabel(a5);
        gbc.gridwidth=GridBagConstraints.REMAINDER;
        setlabel(a6);
        for(i=0;i<42;i++)
        {   if(i%7==6)
               gbc.gridwidth=GridBagConstraints.REMAINDER;
        if(i%7==0)
               gbc.gridwidth=1;
            btn[i]=new Button("  ");
            gb.setConstraints(btn[i], gbc);
            add(btn[i]);
            btn[i].addActionListener(new handact(this));
            }
        
        text=new TextArea();
        gbc.gridheight=5;
        gb.setConstraints(text, gbc);
        add(text);
        gbc.gridwidth=1;
        commit=new Button("提交");
        newpost=new Button("新建");
        gb.setConstraints(newpost, gbc);
        add(newpost);
        gb.setConstraints(konge, gbc);
        add(konge);
        
        gb.setConstraints(commit, gbc);
        add(commit);
        
        newpost.addActionListener(new handact(this));
        commit.addActionListener(new handact(this));
        zhuandao.addActionListener(new handact(this));
        setmonth();
        
        try{
            url="jdbc:odbc:driver={Microsoft Access Driver (*.mdb)};DBQ=test.mdb";
            Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
             conn=DriverManager.getConnection(url);
            
             sta=conn.createStatement();
        
        }catch(Exception e){e.printStackTrace();}
        text.enable(false);
        this.setSize(700, 500);
        this.setVisible(true);
        
    }
    
    protected void setmonth(){
        int year1,month1;
        String year_la,month_la,note="";
        
        
        
        year1=Integer.parseInt(year.getText());
        month1=Integer.parseInt(month.getText());
        xingqi test=new xingqi(year1,month1,1);
        setbuttons(test.runnian(),test.xingqi(),month1);
        
        
    }
    protected void setbuttons(boolean runnian,int xingqi,int yue)
    {
        
        if(runnian && yue==2) longnum=29;
        if(!runnian && yue==2) longnum=28;
        if(yue!=2) longnum =monnum[yue-1];
        startnum=xingqi%7;
        endnum=startnum+longnum;
        for(i=0;i<42;i++)
        {   
            if(i<startnum) btn[i].setLabel("  ");
            else if(i<endnum)
            {
                temp=i-startnum+1;
                s=Integer.toString(temp);
                btn[i].setLabel(s);
                
            }
            else btn[i].setLabel("  ");
        }
        
    }
    
    class handlewin extends WindowAdapter{
        public void windowClosing(WindowEvent e){
            (e.getWindow()).dispose();
            System.exit(0);
        }
        
    }
    
    class handact implements ActionListener
    {
        gridexam a1;
        
        handact(gridexam f){
            a1=f;
        }
        public void actionPerformed(ActionEvent e){
            String s=e.getActionCommand();
            boolean ok=true;
            int num=0;
        
            try{num=Integer.parseInt(s);}
            catch(NumberFormatException ls){ok=true;}
            
            if(num>=1&&num<=31&&ok==true){
                
                a1.yeara=Integer.parseInt(year.getText());
                a1.montha=Integer.parseInt(month.getText());
                a1.daya=num;
                String note="";
                try{
                    String sqls="select * from [note] where year= ? and month=? and day=?";
                    PreparedStatement ps=conn.prepareStatement(sqls);
                    ps.setInt(1, yeara);
                    ps.setInt(2, montha);
                    ps.setInt(3, daya);
                    ResultSet resu=ps.executeQuery();
                    
                    while(resu.next()){
                        note=note+resu.getString("notes")+"\n";
                    }
                }catch(Exception b){b.printStackTrace();};
                text.setText(note);
           
                
            }
            if(s=="转到") setmonth();
            if(s=="新建")    {
                text.setText("");
                text.enable(true);
                a1.xinjian=true;
                System.out.println(a1.xinjian);
            };
        
            if(s=="提交"&& a1.xinjian==true)
            {
                String st=text.getText();
            
                try{
                    String sqls="insert into [note](year,month,day,notes) values(?,?,?,?)";
                    PreparedStatement ps=conn.prepareStatement(sqls);
                    ps.setInt(1, yeara);
                    ps.setInt(2, montha);
                    ps.setInt(3, daya);
                    ps.setString(4, st);
                    ps.executeUpdate();
                    conn.commit();
                }catch(Exception fs){fs.printStackTrace();}
                 a1.xinjian=false;
                 text.enable(false);
                System.out.println(a1.xinjian);
            }
         
        }
        
        
    
    
    
    }

class xingqi{
    private int year,month,day;
    xingqi(int y,int m,int d){
        year=y;month=m;day=d;
        
    }
    private void tiaozheng(){
        if(month<3)
        {
            month=month+12;
            year--;
        }
    }
    public int xingqi(){
        int w=0,c,y;
        c=year/100;y=year-c*100;
        tiaozheng();
        w=y+y/4+c/4-2*c+26*(month+1)/10+day-1;
        w=w%7;
        if(w<0) w=w+7;
        return w;
    }
    public boolean runnian(){
        boolean s=false;
        
        
        s=((year%4==0)&&(year%100!=0))||(year%400==0);
        return s;
    }
}
    
    
}