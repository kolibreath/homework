import java.util.LinkedList;
import java.util.List;

public class morphology {
    static String[] list={"main","int","char","if","else","for","while"};
    static List<Word> words=new LinkedList<>();
        static void scan(String token){
            int index=0;
            int start=0;
            while(index<token.length() && start<token.length()){
                char ch=token.charAt(start);
                if(letter(ch) || digit(ch)){
                    while(letter(ch) || digit(ch)){
                        index++;
                        if(index<token.length())
                            ch=token.charAt(index);
                        else
                            ch='#';//用于退出
                    }
                    if(index>start) {
                        String s = token.substring(start, index);
                        ld(s);
                    }
                    start=index;
                }
                else{
                    if(index+1==token.length())
                    {
                        String s=token.substring(index,index+1);
                        w(s);
                        start=index+1;
                    }
                    else
                    {
                        String s;
                        if(!(letter(token.charAt(index+1)) || digit(token.charAt(index+1))))
                        {
                            char c1=token.charAt(index);
                            char c2=token.charAt(index+1);
                            s=token.substring(index,index+2);
                            index=index+2;
                        }
                        else{
                            s=token.substring(index ,index+1);
                            index=index+1;
                        }
                        w(s);
                        start=index;
                    }
                }
            }
        }
        //检测字母数字
        static void ld(String token) {

            Word word = new Word();
            char ch = token.charAt(0);
            if (letter(ch)) {
                word.typenum = checkKeyWord(token);
                word.word = token;
                words.add(word);
            } else if (digit(ch)) {
                word.word = token;
                word.typenum = 20;
                words.add(word);
            }
        }
        //检测字符
        static void w(String token){
            Word word = new Word();
            char ch=token.charAt(0);
            switch (ch){
                case '=':
                    if(token.length()==1) {
                        word.word = "=";
                        word.typenum = 21;
                        words.add(word);
                        break;
                    }
                    else {
                        char temp = token.charAt(1);
                        if (temp == '=') {
                            word.word = "==";
                            word.typenum = 39;
                            words.add(word);
                            break;
                        }
                    }

                case '+':
                    word.word="+";
                    word.typenum=22;
                    words.add(word);
                    break;

                case '-':
                    word.word="-";
                    word.typenum=23;
                    words.add(word);
                    break;

                case '*':
                    word.typenum=24;
                    word.word="*";
                    words.add(word);
                    break;

                case '/':
                    word.word="/";
                    word.typenum=25;
                    words.add(word);
                    break;

                case '(':
                    word.word="(";
                    word.typenum=26;
                    words.add(word);
                    break;

                case ')':
                    word.word=")";
                    word.typenum=27;
                    words.add(word);
                    break;

                case '[':
                    word.word="[";
                    word.typenum=28;
                    words.add(word);
                    break;

                case ']':
                    word.word="]";
                    word.typenum=29;
                    words.add(word);
                    break;

                case '{':
                    word.word="{";
                    word.typenum=30;
                    words.add(word);
                    break;

                case '}':
                    word.word="}";
                    word.typenum=31;
                    words.add(word);
                    break;

                case ',':
                    word.word=",";
                    word.typenum=32;
                    words.add(word);
                    break;

                case ':':
                    word.word=":";
                    word.typenum=33;
                    words.add(word);
                    break;

                case ';':
                    word.word=";";
                    word.typenum=34;
                    words.add(word);
                    break;

                case '>':
                    if(token.length()==1) {
                        word.word = ">";
                        word.typenum = 35;
                        words.add(word);
                        break;
                    }
                    else {
                        char temp = token.charAt(1);
                        if (temp == '=') {
                            word.word = ">=";
                            word.typenum = 37;
                            words.add(word);
                            break;
                        }
                    }

                case '<':
                    if(token.length()==1) {
                        word.word = "<";
                        word.typenum = 36;
                        words.add(word);
                        break;
                    }
                    else {
                        char temp = token.charAt(1);
                        if (temp == '=') {
                            word.word = "<=";
                            word.typenum = 38;
                            words.add(word);
                            break;
                        }
                    }

                case '!':
                    if(token.length()==1) {
                        word.word = "!";
                        word.typenum = 200;
                        words.add(word);
                        break;
                    }
                    else {
                        char temp = token.charAt(1);
                        if (temp == '=') {
                            word.word = "!=";
                            word.typenum = 40;
                            words.add(word);
                            break;
                        }
                    }

                case '\0':
                    word.word="OVER";
                    word.typenum=1000;
                    words.add(word);
                    break;
                case '#':
                    word.word="OVER";
                    word.typenum=1001;
                    words.add(word);
                    break;

                default:
                    word.word="ERROR";
                    word.typenum=-1;
                    words.add(word);
                    break;
            }
        }
        //判断字母
        static boolean letter(char ch){
            return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
        }
        //判断数字
        static boolean digit(char ch){
            if(ch>='0'&&ch<='9')return true;
            return false;
        }
        //检索关键字
        static int checkKeyWord(String token){
            for(int i=0;i<list.length;i++)
                if(token.equals(list[i]))
                    return i+1;
            return 10;
        }

    }

