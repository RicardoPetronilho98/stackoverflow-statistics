package main.java.engine;

import main.java.common.User;

import java.util.Comparator;

public class ComparatorUserMaiorReputacao implements Comparator<User> {
    /**
     *
     * @param a user 1
     * @param b user 2
     * @return retorna pela ordem decrescente de reputação de um user
     */
    public int compare(User a, User b){
        if(a.getReputacao() == b.getReputacao()){
            if(a.getId() > b.getId()) return -1;
            return 1;
        }
        if(a.getReputacao() > b.getReputacao()) return -1;
        return 1;
    }
}
