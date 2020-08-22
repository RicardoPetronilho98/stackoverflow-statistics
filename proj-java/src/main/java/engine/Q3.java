package main.java.engine;

import main.java.common.Pair;
import main.java.common.Dados;
import main.java.common.Post;

import java.time.LocalDate;

public class Q3 {
    /**
     * Dado um intervalo de tempo arbitrário, a função retorna um par com o número total de
     * posts (identificando perguntas e respostas separadamente) neste período;
     * @param begin ínicio do intrevalo
     * @param end fim do intrevalo
     * @param dados dados
     * @return retorna um par com o número total de
     * posts (identificando perguntas e respostas separadamente) neste período
     */
    public static Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end, Dados dados) {
        long numPerguntas = 0, numRespostas = 0;

        for(Post post : dados.getPostsPorDataCollection(begin, end)) {
            if (post.getTipo() == 1) numPerguntas++;
            else if (post.getTipo() == 2) numRespostas++;
        }

        return new Pair<>(numPerguntas, numRespostas);
    }
}
