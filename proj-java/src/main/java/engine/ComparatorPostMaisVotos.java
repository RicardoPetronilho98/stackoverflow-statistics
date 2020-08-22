package main.java.engine;



import main.java.common.Post;

import java.util.Comparator;


public class ComparatorPostMaisVotos implements Comparator<Post>{

    /**
     * Compara duas faturas por valor.
     * @param p1 post 1
     * @param p2 post 2
     * @return retorna por ordem decrescente do score dos posts
     */
    public int compare(Post p1, Post p2){
        if (p1.getScore() == p2.getScore()) return 0;
        if (p1.getScore() > p2.getScore()) return -1;
        return 1;
    }
}
