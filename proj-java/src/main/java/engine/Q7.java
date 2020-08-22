package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;

import java.time.LocalDate;
import java.util.*;


public class Q7 {
    public static List<Long> mostAnsweredQuestions(Dados dados, int N, LocalDate begin, LocalDate end){

        Collection<Post> postsInDate = dados.getPostsPorDataCollection(begin, end);

        List <Post> postsInType = new ArrayList<>();
        for(Post p : postsInDate){
            if(p.getTipo() == 1){
                postsInType.add(p);
            }
        }
        postsInType.sort(new ComparatorPostAnswerCount());
        int size = postsInType.size();
        if( size > N) size = N;
        List<Long> res = new ArrayList<>(size);
        for(Post p: postsInType) {
            res.add(p.getId());
            size--;
            if (size == 0) break;
        }
        return res;
    }
}
