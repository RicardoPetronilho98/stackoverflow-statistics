package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;
import main.java.common.PostNaoExisteException;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Q8 {

    /**
     * Dado uma palavra, devolve uma lista com os ids de N perguntas cujos títulos a contenham, ordenados por cronologia inversa.
     *
     * @param N número ids de perguntas
     * @param word palavra a ser procurada
     * @param dados dados
     * @return retorna uma lista com os ids
     * @throws PostNaoExisteException caso o post procurado não exista
     */
    public static List<Long> containsWord(int N, String word, Dados dados) throws PostNaoExisteException {

        List<Long> ids = new ArrayList<>();
        Map<Long,Post> posts = dados.getPosts();
        int size;
        String titulo;

        for(Post p: posts.values()){

            if (  p.getTipo() != 1 || ( titulo = p.getTitulo() ).isEmpty() || !titulo.contains(word) ) continue;

            ids.add(p.getId());
        }

        ids = STDSort.sortPostsByInvertedCronology(ids, dados);

        if (ids.size() < N) size = ids.size();
        else size = N;

        // NOTA: o ultimo index é exclusivo, por isso na realidade a sub lista vai de 0 a (size - 1)
        return ids.subList(0, size);
    }
}
