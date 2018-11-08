import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class boolsearch {
    public static void main(String[]args) {
        List<word> words = new LinkedList<>();//总链
        List<String> w=new LinkedList<>();//单词链表
        List<String> ss = new LinkedList<>();
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC1.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC2.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC3.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC4.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC5.TXT");

        FileReader fileReader;
        {
            try {
                for(String s : ss){
                    fileReader = new FileReader(s);
                    int i;
                    String str="";
                    while((i=fileReader.read())>-1) {
                        str = str + (char) i;
                    }
                    String[] wo=str.split(" ");//用空格分开
                    int index=ss.indexOf(s)+1;//找出是哪一个文件
                    for(String wod : wo) {
                        if (w.contains(wod)) {//已经有这个单词
                            int in = w.indexOf(wod);
                            word q = words.get(in);
                            q.doc.add(index);
                        }
                        else {
                            word ww = new word();
                            ww.w = wod;
                            ww.doc.add(index);
                            words.add(ww);
                            w.add(wod);
                        }
                    }
                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        for(word p : words){
            System.out.print("word:"+p.w+"   ");
            for(int i:p.doc){
                System.out.print(i+"  ");
            }
            System.out.print("\n");
        }

        Scanner scanner=new Scanner(System.in);
        System.out.print("please input the search");
        String want=scanner.nextLine();
        want=want+" OR ";
            String[] ors = want.split(" OR ");//先用or分开

        List<Integer> orlist=new LinkedList<>();

            for (String orss : ors) {

                orss=orss+" AND ";
                String[] ands = orss.split(" AND ");//再用and分开

                List<String> n=new LinkedList<>();
                List<String>m =new LinkedList<>();

                for (String andss : ands) {
                    if(andss.contains("NOT")){
                        andss=andss.replace("NOT ","");//将not以及空格删掉
                        n.add(andss);//把他放到有not的list中
                    }
                    else{
                        andss=andss.replace(" ","");
                        m.add(andss);//将他放到没有not 的list中
                }
            }
            List<Integer> andlist=new LinkedList<>();
                for(int k=1;k<=5;k++)
                    andlist.add(k);

                for(String i : n){
                    andlist=AND(andlist,nofind(i,w,words));
                }
                for(String j : m){
                    andlist=AND(andlist,find(j,w,words));
                }

            orlist=OR(orlist,andlist);
    }

    if(orlist.isEmpty())
        System.out.print("no file");
            else{
        for(Integer i : orlist){
            System.out.print(i.intValue()+"  ");
        }
    }

    }
    //查找单词出现的文章集合
   public static List<Integer> find(String s,List<String>wlist,List<word>w){
        if(wlist.contains(s))
        {
            int index=wlist.indexOf(s);
            return w.get(index).doc;
        }
        else
            return null;
    }
    //求文章集合的补集
    public static List<Integer> nofind(String s,List<String>wlist,List<word>w){
        if(wlist.contains(s)){
            int index=wlist.indexOf(s);
            List<Integer> d=w.get(index).doc;
            List<Integer> nod=new LinkedList<>();
            for(int i=1;i<=5;i++){
                if(d.contains(i))
                    continue;
                else
                {
                    nod.add(i);
                }
            }
            return nod;//不包含s的文档集合
        }
        else {
            List<Integer> o = new LinkedList<>();
            for (int i = 1; i <= 5; i++) {
                o.add(i);
            }
            return o;
        }
    }
    //求交集
    public static List<Integer> AND(List<Integer> s1,List<Integer>s2){
        List<Integer> And=new LinkedList<>();
        for(Integer i : s1){
            if(s2.contains(i))
                And.add(i);
        }
        return And;
    }
    //求并集
    public static List<Integer> OR(List<Integer> s1,List<Integer>s2){
        List<Integer> or=new LinkedList<>();
        for(Integer i : s1){
            or.add(i);
        }
        for(Integer j : s2){
            if(!or.contains(j)){
                or.add(j);
            }
        }
        return or;
    }

}
