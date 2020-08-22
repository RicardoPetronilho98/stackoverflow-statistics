package main.java.engine;

import main.java.common.Post;

import java.util.Comparator;

public class ComparatorPostAnswerCount implements Comparator<Post> {

    /**
     *
     * @param p1 post 1
     * @param p2 post 2
     * @return retorna pela ordem decrescente do número de respostas de posts
     */

    public int compare(Post p1, Post p2){
        if ( p1.getAnswerCount() == p2.getAnswerCount() ){
            if(p1.getId() > p2.getId()) return -1;
            return 1;
        }
        else if ( p1.getAnswerCount() > p2.getAnswerCount() ) return -1;
        else return 1;
    }
}
