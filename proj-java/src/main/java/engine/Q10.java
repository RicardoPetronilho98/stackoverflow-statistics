package main.java.engine;

import main.java.common.*;

public class Q10 {

    /**
     * Dado um id de uma pergunta retorna o id da melhor resposta.
     *
     * @param id id da pergunta
     * @param dados base de dados
     * @return Retorna o id da melhor resposta
     * @throws IdNegativoException caso o id dado seja negativo
     * @throws PostNaoExisteException caso não exista um Post com o id dado
     * @throws UserNaoExisteException caso não exista um User com o UserId procurado
     * @throws PostNaoEUmaPerguntaException caso o Post com o id dado não seja uma pergunta
     */
    public static long better_answer(long id, Dados dados) throws IdNegativoException, PostNaoExisteException, UserNaoExisteException, PostNaoEUmaPerguntaException {

        if (id < 0) throw new IdNegativoException(Long.toString(id));

        Post post = dados.getPost(id);

        long max = -1, resId = -1, media, Scr, Rep, Vot, Comt;

        if ( post.getTipo() != 1) throw new PostNaoEUmaPerguntaException(Long.toString(id));

        for(Post p: dados.getPosts().values()){

            if ( p.getTipo() != 2 || p.getParentId() != id) continue; // não é uma resposta á pergunta

            User user = dados.getUser(p.getUserId());

            Scr = p.getScore();
            Rep = user.getReputacao();
            Vot = user.contavotos();
            Comt = p.getCommentCount();

            media = (long) (Scr * 0.45 + Rep * 0.25 + Vot * 0.2 + Comt * 0.1);

            if (media > max){
                resId = p.getId();
                max = media;
            }
        }

        return resId;
    }
}
