import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class vectorSpace {
    public static void main(String[]args){
        List<String> ss = new LinkedList<>();
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC1.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC2.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC3.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC4.TXT");
        ss.add("C:\\Users\\于田\\信息检索\\src\\DOC5.TXT");

        Scanner s=new Scanner(System.in);
        System.out.println("please input search");
        String search=s.nextLine();

        String []searchword=search.split(" ");
        HashMap<String ,Integer>map=new HashMap<>();
        for(String word:searchword){
            if(word.equals("a")|| word.equals("and") || word.equals("on") || word.equals("in") ||word.equals("of"))
                continue;
            else {
                if (map.containsKey(word)) {
                    int c = map.get(word);
                    c++;
                    map.put(word, c);
                } else {
                    map.put(word, 1);
                }
            }
        }
        List<wordVector>w=new LinkedList<>();
        List<docvetcor>d=new LinkedList<>();
        search(w,map,ss);
        HashMap<String,Float>docmap=new HashMap<>();
        for(String adress : ss){
            float goal=doc(d,w,adress);
            docmap.put(adress,goal);
        }
        Comparator<Map.Entry<String ,Float>>valuecompare=new Comparator<Map.Entry<String, Float>>() {
            @Override
            public int compare(Map.Entry<String, Float> o1, Map.Entry<String, Float> o2) {
                return o2.getValue().compareTo(o1.getValue());
            }
        };

        List<Map.Entry<String,Float>> doclist=new ArrayList<>(docmap.entrySet());
        Collections.sort(doclist,valuecompare);

       for(Map.Entry<String,Float> m : doclist){
           System.out.println(m.getKey()+"  "+m.getValue());
        }
    }
    static int df(List<String> adress,String word) {
        int count=0;
       //读取文件
        FileReader fileReader;
        {
            try {
                for (String s : adress) {
                    fileReader = new FileReader(s);
                    int i;
                    String str = "";
                    while ((i = fileReader.read()) > -1) {
                        str = str + (char) i;
                    }
                    if(str.contains(word))
                        count++;
                    else
                    continue;
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return count;
    }
    static int tf(String word,String str){
        int count=0;
        String []strword=str.split(" ");
        for(String s : strword){
            if(s.equals(word))
              count++;
        }
        return count;
    }
    static float sum(List<wordVector>w){
        float sum=0;
        for(wordVector ws:w){
            sum+=ws.w*ws.w;
        }
        sum= (float) Math.sqrt(sum);
        return sum;
    }
    static float searchnormaliz(wordVector word,float sum){
        return (float)word.w/sum;
    }
    static float summ(List<docvetcor>d){
        float sum=0;
        for(docvetcor ds:d){
            sum+=ds.wd;
        }
        sum=(float)Math.sqrt(sum);
        return sum;
    }
    static void docnormaliz(docvetcor ds,float sum){
            ds.wd=ds.wd/sum;
    }
    static int max(HashMap<String,Integer>map){
        int max=0;
        for(String key:map.keySet()){
            int c=map.get(key);
            if(max>c);
            max=c;
        }
        return max;
    }
    static void search(List<wordVector>w,HashMap<String,Integer>map,List<String>adress){
        int max=max(map);
        int N=100;
        for(String key : map.keySet()){
            wordVector word=new wordVector();
            word.word=key;
            int t=map.get(key);
            word.tf=(float)(0.5+(0.5*t)/max);
            word.df=(float)df(adress,key);
            word.idf= (float) Math.log10(N/word.df);

            word.w=word.idf*word.tf;
            w.add(word);
        }
        float sum=sum(w);
        for(wordVector wv:w){
            wv.w=wv.w/sum;
        }
    }
    static float doc(List<docvetcor>d,List<wordVector>w,String s) {
        float goal=0;
        FileReader fileReader;
        {
            try {
                fileReader = new FileReader(s);
                int i;
                String str = "";

                while ((i = fileReader.read()) > -1) {
                    str = str + (char) i;
                }
                String[]strw=str.split(" ");
                for(wordVector wv:w){
                    docvetcor dv=new docvetcor();
                    dv.word=wv.word;
                    dv.idfd=wv.idf;
                    int c=0;
                    for(String sw:strw){
                        if(sw.equals(dv.word))
                            c++;
                    }
                    dv.tfd=c;
                    dv.wd=dv.idfd*dv.tfd;
                    d.add(dv);
                }
               float sum=summ(d);
               int index=0;
                for(docvetcor dv: d){
                    if(sum==0)
                        dv.wd=0;
                    else
                        dv.wd=dv.wd/sum;
                    float term=w.get(index).w;
                    dv.mul=dv.wd*term;
                    goal+=dv.mul;
                    //System.out.println(s+"  "+goal);
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        d.clear();
        return goal;//文档的得分
    }
}
