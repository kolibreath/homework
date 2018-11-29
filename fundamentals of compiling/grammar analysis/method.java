import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.util.LinkedList;
import java.util.List;

public class method {
     static int  index=0;
    public static void main(String []args){
        String input="begin { x=3 ; if(x==2) { y=3; } } end";
        String input2="begin{ if( ) y=3; }end";
        String input3="begin{ while( x<3 ) {  y=x+1 ; } } end";
            String []in=input3.split(" ");//空格分割
            for(String token : in) {
                morphology.scan(token);//进行词法分析，得到word list
            }

        program(morphology.words);
        for(Word s : morphology.words){
            System.out.print(s.word + "  ");
        }
    }
    static void program(List<Word> w){
        Word ww=w.get(index);
        String sw=ww.word;
        if(sw.equals("begin"))
        {
            index++;
            if(statementss(w)) {//语句串
                index++;
                if (w.get(index).word.equals("end")) {
                    System.out.println("正确结束！");
                } else {
                    System.out.println("error!!"+"  index->  "+index);
                }
            }
            else
                System.out.println("error!!"+"  index->  "+index);
        }
        else
        {
            System.out.println("error!!"+"  index->  "+index);
        }
    }
    static boolean statementss(List<Word>w){//语句块
        if(w.get(index).word.equals("{"))
        {
            index++;
            if(statements(w))
            {
                index++;
                if(w.get(index).word.equals("}"))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    static boolean statements(List<Word> w){//语句串
        if(statement(w))
        {
            index++;
            while(w.get(index).word.equals(";")){
                index++;
                if(statement(w))
                    index++;
            }
            index--;
            return true;
        }
        else
            return false;
    }
    static boolean statement(List<Word> w){//语句
        if(assginment(w) || condition(w) || loop(w)){
            return true;
        }
        else
            return false;
    }
    static boolean assginment(List<Word>w){//赋值语句
        if(ID(w))
        {
            index++;
            if(w.get(index).word.equals("=")) {
                index++;
                if (expression(w))
                        return true;
                    else

                    return false;
                }

                else
            {
                index--;
                return false;
            }
        }
            else
                return false;
    }
    static boolean condition(List<Word>w){//条件语句
        if(w.get(index).word.equals("if"))
        {
            index++;
            if(w.get(index).word.equals("("))
            {
                index++;
                if(conditions(w))
                {
                    index++;
                    if(w.get(index).word.equals(")"))
                    {
                        index++;
                        if(statementss(w))
                        {
                            return true;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    static boolean loop(List<Word>w){//循环语句
        if(w.get(index).word.equals("while")) {
            index++;
            if (w.get(index).word.equals("(")) {
                index++;
                if (conditions(w)) {
                        index++;
                        if(w.get(index).word.equals(")")) {
                            index++;
                            if (statementss(w))
                                return true;
                            else
                                return false;
                        }
                        else
                            return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    static boolean conditions(List<Word>w){//条件
        if(expression(w)){
            index++;
            if(operator(w))
            {
                index++;
                if(expression(w))
                    return true;
                else
                    return false;

            }
            else
                return false;
        }
        else
            return false;
    }
    static boolean expression(List<Word>w){//表达式
        if(term(w)) {
            index++;
            while((w.get(index).word.equals("+") ||w.get(index).word.equals("-")))
            {
                index++;
                if(term(w))
                {
                    index++;
                }
                else
                    return false;
            }
            index--;
            return true;
        }
        else
            return false;
    }
    static boolean term(List<Word>w){//项
        if(factor(w))
        {
            index++;
            while(w.get(index).word.equals("*") || w.get(index).word.equals("/"))
            {
                index++;
                if(factor(w))
                    return true;
                else
                    return false;
            }
            index--;
            return true;
        }
        else
            return false;
    }
    static boolean factor(List<Word>w){//因子
       if(ID(w) || NUM(w))
       {
           return true;
       }
       if(w.get(index).word.equals("("))
       {
           index++;
           if(expression(w))
           {
               index++;
               if(w.get(index).word.equals(")"))
                   return true;
               else
                   return false;
           }
           else
               return false;
       }
       else
           return false;
    }
    static boolean ID(List<Word>w){
        String s=w.get(index).word;//取出当前的单词
        int type=w.get(index).typenum;
        if(type==10 || type==4 || type==7)
           return true;
        else
            return false;
    }
    static boolean NUM(List<Word>w){
        String s=w.get(index).word;//取出当前的单词
        int type=w.get(index).typenum;
        if(type==20)
            return true;
        else
            return false;
    }
    static boolean operator(List<Word>w){//操作符
        List<String> operators=new LinkedList<>();
        operators.add("<=");
        operators.add(">=");
        operators.add("==");
        operators.add("!=");
        operators.add(">");
        operators.add("<");
        if(operators.contains(w.get(index).word))
            return true;
        else
            return false;
    }
}
