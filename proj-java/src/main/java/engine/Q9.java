package main.java.engine;

import main.java.common.Dados;
import main.java.common.Post;
import main.java.common.PostNaoExisteException;
import main.java.common.UserNaoExisteException;

import java.util.*;
import java.util.stream.Collectors;

public class Q9 {
    /**
     * Devolve a lista com os IDS das N perguntas onde dois utilizadores participaram, via pergunta ou resposta.
     * @param N número de perguntas
     * @param id1 id do utilizador 1
     * @param id2 id do utilizador 2
     * @param dados base de dados
     * @throws UserNaoExisteException caso não exista utilizador
     * @throws PostNaoExisteException caso não exista post
     * @return retorna a lista com os IDS das N perguntas onde dois utilizadores participaram, via pergunta ou resposta.
     */
    public static List<Long> bothParticipated(int N, long id1, long id2, Dados dados) throws UserNaoExisteException, PostNaoExisteException{
        ArrayList<Long> res = new ArrayList<>();

            for(Long postId1 : dados.getUser(id1).getPostsIds()){
                Post postUser1 = dados.getPost(postId1);
                for(Long postId2 : dados.getUser(id2).getPostsIds()){
                    Post postUser2 = dados.getPost(postId2);
                    if(postUser1.getTipo() == 1 && postUser2.getTipo() == 2 && postUser1.getTipo() == postUser2.getParentId() && !res.contains(postId1))
                        res.add(postId1);
                    if(postUser1.getTipo() == 2 && postUser2.getTipo() == 1 && postUser1.getParentId() == postUser2.getTipo() && !res.contains(postId2))
                        res.add(postId2);
                    if(postUser1.getTipo() == 2 && postUser2.getTipo() == 2 && postUser1.getParentId() == postUser2.getParentId() && !res.contains(postUser1.getParentId()))
                        res.add(postUser1.getParentId());
                }
            }

            STDSort.sortPostsByInvertedCronology(res, dados);

        return res.stream().limit(N).collect(Collectors.toList());
    }
}

