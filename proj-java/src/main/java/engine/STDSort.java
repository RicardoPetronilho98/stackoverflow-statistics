/**
 * class que contém vários métodos utilizados para ordenar dados.
 */

package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;
import main.java.common.PostNaoExisteException;

import java.util.ArrayList;
import java.util.List;

public class STDSort {

    /**
     * Devolve uma lista de ids de posts ordenada por cronologia inversa.
     *
     * @param postsIds lista de ids de posts
     * @param dados base de dados
     * @return retorna a lista de ids de posts
     * @throws PostNaoExisteException caso não exista o Post com o id procurado
     */
    public static List<Long> sortPostsByInvertedCronology(List<Long> postsIds, Dados dados) throws PostNaoExisteException {
        List<Post> list = new ArrayList<>(postsIds.size());
        for(Long id: postsIds) list.add(dados.getPost(id));
        list.sort(new ComparatorPostData().reversed());
        List<Long> res = new ArrayList<>(list.size());
        for(Post post : list) res.add(post.getId());
        return res;
    }
}
