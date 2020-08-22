package main.java.engine;

import main.java.common.*;

import java.util.List;

public class Q5 {

    private static final int N = 10;

    /**
     * Dado um id de utilizador, devolver a informação do seu perfil (short bio) e os ids dos seus 10 últimos posts
     * perguntas ou respostas), ordenados por cronologia inversa.
     *
     * @param id id do utilizador
     * @param dados base de dados
     * @return retorna um par (shorbio, ids de posts)
     * @throws PostNaoExisteException caso não exita o post procurado
     * @throws UserNaoExisteException caso não exista user com o id especificado
     * @throws UserNaoTemPostsException caso exista user mas o mesmo não tem posts
     */
    public static Pair<String, List<Long>> getUserInfo(long id, Dados dados) throws PostNaoExisteException, UserNaoExisteException, UserNaoTemPostsException{

        User user = dados.getUser(id);
        List<Long> postsIds = user.getPostsIds();
        int size;

        if (postsIds.isEmpty()) throw new UserNaoTemPostsException(Long.toString(id));

        postsIds = STDSort.sortPostsByInvertedCronology(postsIds, dados); // ordena os ids dos posts por cronologia inversa

        if (postsIds.size() < N) size = postsIds.size();
        else size = N;

        return new Pair<>(user.getBio(), postsIds.subList(0, size));
    }
}
