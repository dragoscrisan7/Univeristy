package org.example.features.login;

import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Issue;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.Qualifier;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.example.steps.serenity.EndUserSteps;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/LoginCredentials.csv")
public class LoginWithGoodCredentialsStory {
    @Managed(uniqueSession = true)
    public WebDriver webdriver;

    @Steps
    public EndUserSteps alexandra;

    public String email;
    public String password;
    public String username;

    @Qualifier
    public String getQualifier() {
        return email;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Issue("#WIKI-1")
    @Test
    public void log_in_with_valid_credentials_should_prompt_with_user() {
        alexandra.goes_to_the_home_page();
        alexandra.signs_in();
        alexandra.signs_in_with_imdb();
        alexandra.types_email(getEmail());
        alexandra.types_password(getPassword());
        alexandra.submits_sign_in_with_credentials();
        alexandra.should_see_the_username(getUsername());
    }
}