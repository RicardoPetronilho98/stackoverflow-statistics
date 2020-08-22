package main.java.li3;

import main.java.common.*;
import main.java.engine.Q8;
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

public class TesteQ8 {

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

            List<Long> ids1 = Q8.containsWord(10, "kde", dados);
            System.out.println(ids1);

            List<Long> ids2 = Q8.containsWord(10, "glib", dados);
            System.out.println(ids2);

            Set<Long> arr1 = new HashSet<>(Arrays.asList(new Long[]{980835L, 979082L, 974117L, 974105L, 973832L, 971812L, 971056L, 968451L, 964999L, 962770L}));
            System.out.println( arr1.equals(new HashSet<>(ids1) ));

            Set<Long> arr2 = new HashSet<>(Arrays.asList(new Long[]{979114L, 975754L, 948816L, 941569L, 921207L, 916518L, 905536L, 899256L, 898568L, 881969L}));
            System.out.println( arr2.equals(new HashSet<>(ids2)) );

        } catch (SAXException e){
            System.out.println("Erro: SAXExcpetion");
            e.printStackTrace();
        } catch (IOException e){
            System.out.println("Erro: IOExcpetion");
            e.printStackTrace();
        } catch (ParserConfigurationException e){
            System.out.println("Erro: ParserConfigurationException");
            e.printStackTrace();
        } catch (PostNaoExisteException e){
            System.out.println("Erro: PostNaoExisteException");
            e.printStackTrace();
        }
    }
}