package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;
import main.java.common.PostNaoExisteException;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Q4 {
    /**
     * Dado um intervalo de tempo arbitrário, a função retorna uma lista com os posts identificados com a respectiva tag, esta lista está ordenada por cronologia inversa.
     * @param tag tag a ser encontrada
     * @param begin inicio do intrevalo
     * @param end fim do intrevalo
     * @param dados base de dados
     * @throws PostNaoExisteException caso não exista post
     * @return retorna uma lista com os posts identificados com a respectiva tag, esta lista está ordenada por cronologia inversa.
     */
    public static List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end, Dados dados) throws PostNaoExisteException{
        List<Long> postsIds = new ArrayList<Long>();

        for(Post post : dados.getPostsPorDataCollection(begin, end)) {
            if(post.getTipo() == 1 && post.getTags().contains(tag)) {
                postsIds.add(post.getId());
            }

        }

        postsIds = STDSort.sortPostsByInvertedCronology(postsIds, dados);

        return postsIds;
    }
}
