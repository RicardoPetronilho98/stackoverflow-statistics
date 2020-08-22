package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;

import java.util.*;
import java.time.LocalDate;

/**
 *  Dado um intervalo de tempo arbitr´ario, devolver os IDs
 * das N respostas com mais votos, em ordem decrescente do n´umero de votos;
 */

public class Q6 {

    public static List<Long> mostVotedAnswers(Dados dados, int N, LocalDate begin, LocalDate end) {


        List<Post> list = new ArrayList<>(dados.getPostsPorDataCollection(begin, end));

        int size = list.size();

        list.sort(new ComparatorPostMaisVotos());

        if (size > N) size = N;

        List<Long> res = new ArrayList<>(size);
        for(Post p: list) {
            if(p.getTipo() == 2) {
                res.add(p.getId());
                size--;
            }
            if (size == 0) break;
        }

        return res;
    }
}
