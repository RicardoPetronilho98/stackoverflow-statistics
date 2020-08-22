package main.java.li3;

import main.java.common.*;
import main.java.engine.Q5;
import main.java.engine.TCDExample;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class TesteQ5 {

    public static void main (String[] agrs){

        Dados dados;

        try {

            SAXParserFactory spf = SAXParserFactory.newInstance();
            spf.setNamespaceAware(true);
            SAXParser saxParser = spf.newSAXParser();

            TagsParser handlerTags = new TagsParser(new Dados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Tags.xml"),  handlerTags);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Tags.xml"),  handlerTags);

            UsersParser handlerUsers = new UsersParser(handlerTags.getBaseDeDados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Users.xml"),  handlerUsers);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Users.xml"),  handlerUsers);

            PostsParser handlerPosts = new PostsParser(handlerUsers.getDados());
            //saxParser.parse(STDSort.convertToFileURL("../../android/Posts.xml"),  handlerPosts);
            saxParser.parse(TCDExample.convertToFileURL("../../ubuntu/Posts.xml"),  handlerPosts);

            dados = handlerPosts.getDados(); // base de dados toda carregada

            Pair<String, List<Long>> pair1 = Q5.getUserInfo(15811, dados);
            System.out.println(pair1);

            Pair<String, List<Long>> pair2 = Q5.getUserInfo(449, dados);
            System.out.println(pair2);

            Set<Long> arr1 = new HashSet<>(Arrays.asList(new Long[]{982507L, 982455L, 980877L, 980197L, 980189L, 976713L, 974412L, 974359L, 973895L, 973838L}));
            System.out.println( arr1.equals(new HashSet<>(pair1.getSnd())) );

            Set<Long> arr2 = new HashSet<>(Arrays.asList(new Long[]{978770L, 978765L, 976007L, 972308L, 972015L, 963650L, 961606L, 960465L, 953933L, 948292L}));
            System.out.println( arr2.equals(new HashSet<>(pair2.getSnd())) );

        } catch (SAXException e){
            System.out.println("Erro: SAXExcpetion");
            e.printStackTrace();
        } catch (IOException e){
            System.out.println("Erro: IOExcpetion");
            e.printStackTrace();
        } catch (ParserConfigurationException e){
            System.out.println("Erro: ParserConfigurationException");
            e.printStackTrace();
        } catch (UserNaoExisteException e){
            System.out.println("Erro: UserNaoExisteException");
            e.printStackTrace();
        } catch (UserNaoTemPostsException e) {
            System.out.println("Erro: UserNaoTemPostsException");
            e.printStackTrace();
        } catch (PostNaoExisteException e) {
            System.out.println("Erro: PostNaoExisteException");
            e.printStackTrace();
        }
    }
}

