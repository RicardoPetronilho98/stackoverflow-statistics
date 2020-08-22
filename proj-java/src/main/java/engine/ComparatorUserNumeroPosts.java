package main.java.engine;

import main.java.common.User;

import java.util.Comparator;

public class ComparatorUserNumeroPosts implements Comparator<User>{
    /**
     * Compara dois users, através do seu número de posts (perguntas + respostas).
     * @param u1 utilizador 1
     * @param u2 utilizador 2
     * @return retorna pela ordem decrescente do número de posts (perguntas * respostas)
     */
    public int compare(User u1, User u2){
        if(u1.getNumeroPosts() == u2.getNumeroPosts()) return 0;
        else if (u1.getNumeroPosts() > u2.getNumeroPosts()) return -1;
        else return 1;
    }
}
