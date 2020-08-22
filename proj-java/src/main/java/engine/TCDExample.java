package main.java.engine;

import main.java.common.*;
import main.java.li3.TADCommunity;
import org.xml.sax.SAXException;

import javax.xml.parsers.*;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.List;

public class TCDExample implements TADCommunity {

    private MyLog qelog;
    private Dados dados;

    /**
     * Devolve o caminho para o ficheiro necessário á execução o método parse() da class SAXParser.
     *
     * @param filename nome do ficheiro
     * @return retorna o caminho para o ficheiro
     */
    public static String convertToFileURL(String filename) {
        return new File(filename).getAbsolutePath();
    }

    public void init() {
        this.qelog = new MyLog("queryengine");
    }

    /**
     * Iniciliza a base de dados e carrega toda a informação necessária á execução das queries, dos ficheiros para estrutura.
     *
     * @param dumpPath diretoria onde estão localizados os ficheiros .xml
     */
    public void load(String dumpPath) {

        this.dados = new Dados();

        try {

            SAXParserFactory spf = SAXParserFactory.newInstance();
            spf.setNamespaceAware(true);
            SAXParser saxParser = spf.newSAXParser();

            TagsParser handlerTags = new TagsParser(this.dados);
            saxParser.parse(TCDExample.convertToFileURL(dumpPath + "Tags.xml"), handlerTags);

            this.dados = handlerTags.getBaseDeDados();

            UsersParser handlerUsers = new UsersParser(this.dados);
            saxParser.parse(TCDExample.convertToFileURL(dumpPath + "Users.xml"), handlerUsers);

            this.dados = handlerUsers.getDados();

            PostsParser handlerPosts = new PostsParser(handlerUsers.getDados());
            saxParser.parse(TCDExample.convertToFileURL(dumpPath + "Posts.xml"), handlerPosts);

            this.dados = handlerPosts.getDados(); // base de dados toda carregada

        } catch (SAXException e) {
            System.out.println("Erro: SAXExcpetion");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Erro: IOExcpetion");
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            System.out.println("Erro: ParserConfigurationException");
            e.printStackTrace();
        }
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {

        Pair<String,String> res = null;

        try{
            res = Q1.infoFromPost(this.dados, id);
        }  catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: Post com id dado não existe!");
        }  catch (UserNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método infoFromPost() - User procurado não encontrado!");
        } catch (IdNegativoException e){
            e.printStackTrace();
            System.out.println("Erro: id dado é negativo!");
        }

        return res;
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return Q2.topMostActive(N, this.dados);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return Q3.totalPosts(begin, end, this.dados);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {

        List<Long> res = null;

        try{
            res = Q4.questionsWithTag(tag, begin, end, this.dados);
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método questionsWithTag() - Post procurado não encontrado!");
        }

        return res;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {

        Pair<String, List<Long>> res = null;

        try {
            res = Q5.getUserInfo(id, this.dados);
        } catch (UserNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: ID introduzido não corresponde a nenhum utilizador!");
        } catch (UserNaoTemPostsException e){
            e.printStackTrace();
            System.out.println("Erro: Utilizador existe mas não contém nenhum post!");
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método getUserInfo() - Post procurado não encontrado!");
        }

        return res;
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return Q6.mostVotedAnswers(this.dados, N, begin, end);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return Q7.mostAnsweredQuestions(this.dados, N, begin, end);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {

        List<Long> res = null;

        try {
            res = Q8.containsWord(N, word, this.dados);
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método containsWord() - Post procurado não encontrado!");
            System.exit(-1);
        }

        return res;
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {

        List<Long> res = null;

        try{
            res = Q9.bothParticipated(N, id1, id2, this.dados);
        } catch (UserNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: id introduzido não corresponde a nenhum utilizador!");
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método bothParticipated() - Post procurado não encontrado!");
        }

        return res;
    }

    // Query 10
    public long betterAnswer(long id) {

        long res = -1;

        try {
            res = Q10.better_answer(id, this.dados);
        } catch (UserNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: ID introduzido não corresponde a nenhum utilizador!");
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método getUserInfo() - Post procurado não encontrado!");
        } catch (IdNegativoException e){
            e.printStackTrace();
            System.out.println("Erro: ID introduzido é negativo!");
        } catch (PostNaoEUmaPerguntaException e){
            e.printStackTrace();
            System.out.println("Erro: Post não é uma pergunta!");
        }

        return res;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {

        List<Long> res = null;

        try {
            res = Q11.mostUsedBestRep(this.dados, N, begin, end);
        } catch (TagNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método mostUsedBestRep() - Tag procurada não encontrada!");
        } catch (PostNaoExisteException e){
            e.printStackTrace();
            System.out.println("Erro: occoreu um erro interno no método mostUsedBestRep() - Post procurado não encontrado!");
        }

        return res;
    }

    public void clear(){

    }
}