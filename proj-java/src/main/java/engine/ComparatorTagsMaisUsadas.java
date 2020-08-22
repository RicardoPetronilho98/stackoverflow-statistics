package main.java.engine;

import java.util.Comparator;
import main.java.common.Pair;

public class ComparatorTagsMaisUsadas implements Comparator<Pair> {

    /**
     *
     * @param a Pair 1
     * @param b Pair 2
     * @return retorna por ordem decrescente pelo numero de contadores de uma string e caso sejam iguais pelo id
     */

    public int compare(Pair a, Pair b){
        if(a == b) return 0;
        if(a.getSnd() == b.getSnd()){
            if((Long)a.getFst() < (Long) b.getFst()) return -1;
            return 1;
        }
        if((Long)a.getSnd() > (Long)b.getSnd()) return -1;
        return 1;
    }
}
