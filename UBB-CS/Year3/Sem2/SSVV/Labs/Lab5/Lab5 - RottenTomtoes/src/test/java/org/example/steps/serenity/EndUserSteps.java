package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import org.example.pages.RottenTomatoesPage;

import java.util.List;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;
import static org.hamcrest.Matchers.hasItem;
import static org.hamcrest.Matchers.isEmptyString;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.Matchers.equalTo;
public class EndUserSteps {

    RottenTomatoesPage rottenTomatoesPage;

    @Step
    public void enters(String keyword) {
        rottenTomatoesPage.enter_keywords(keyword);
    }

    @Step
    public void starts_search() {
        rottenTomatoesPage.lookup_data();
    }

    @Step
    public void should_see_movie_name(String name, List<String> movies) {
        assertThat(rottenTomatoesPage.getMovieName(movies), equalTo(name));
    }

    @Step
    public void goes_to_the_home_page() {
        rottenTomatoesPage.open();
    }

    @Step
    public void signs_in() {
        rottenTomatoesPage.main_sign_in();
    }

    @Step
    public void signs_in_with_imdb() {
        rottenTomatoesPage.sign_in_with_imdb();
    }

    @Step
    public void types_email(String email) {
        rottenTomatoesPage.enter_email(email);
    }

    @Step
    public void types_password(String password) {
        rottenTomatoesPage.enter_password(password);
    }

    @Step
    public void submits_sign_in_with_credentials() {
        rottenTomatoesPage.sign_in_with_credentials();
    }

    @Step
    public void should_see_the_username(String username) {
        assertThat(rottenTomatoesPage.getCurrentUserLoggedIn(), equalTo(username));
    }

    @Step
    public void looks_for(String term) {
        enters(term);
        starts_search();
    }

    @Step
    public void should_see_invalid_search_information(String data){
        assertThat(rottenTomatoesPage.getNoResults(), equalTo(data));
    }

    @Step
    public void should_see_incorrect_password_prompt() {
        assertThat(rottenTomatoesPage.getAlertPrompt(), not(isEmptyString()));
    }

    @Step
    public void should_see_search_information(String data) {
        assertThat(rottenTomatoesPage.getList(), hasItem(containsString(data)));
    }
}