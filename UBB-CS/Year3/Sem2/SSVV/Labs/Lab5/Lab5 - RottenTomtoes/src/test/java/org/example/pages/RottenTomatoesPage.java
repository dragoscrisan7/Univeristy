package org.example.pages;

import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import net.serenitybdd.core.pages.WebElementFacade;
import net.thucydides.core.annotations.findby.FindBy;
import net.thucydides.core.pages.PageObject;

import java.util.List;
import java.util.stream.Collectors;

@DefaultUrl("https://www.rottentomatoes.com/")
public class RottenTomatoesPage extends PageObject {

    @FindBy(className = "search-text")
    private WebElementFacade searchOnRottenTomatoes;

    @FindBy(css = "#header-main > search-algolia > search-algolia-controls > a > rt-icon")
    private WebElementFacade lookupButton;

    @FindBy(className = "navbar__user")
    private WebElementFacade signInButton;

    @FindBy(id = "ap_email")
    private WebElementFacade emailInput;

    @FindBy(id = "ap_password")
    private WebElementFacade passwordInput;

    @FindBy(id = "signInSubmit")
    private WebElementFacade signInRealButton;

    public void enter_keywords(String keyword) {
        searchOnRottenTomatoes.type(keyword);
    }

    public void lookup_data() {
        lookupButton.click();
    }

    public List<String> getList() {
        // Wait for the search results to load
        waitForRenderedElements(By.cssSelector("search-page-manager"));

        // Locate the main container of the search results
        WebElementFacade movieList = find(By.cssSelector("search-page-result ul"));

        // Extract the text from each relevant <a> tag within the nested elements
        return movieList.findElements(By.cssSelector("search-page-media-row")).stream()
                .map(row -> row.findElement(By.cssSelector("a.unset"))
                        .getText())
                .collect(Collectors.toList());
    }

    public String getNoResults() {
        WebElementFacade div = find(By.className("fAaPAY"));
        return div.getText();
    }

    public String getMovieName(List<String> moviesList) {
        if (moviesList.isEmpty()) {
            return "";
        }
        return moviesList.get(0);
    }

    public void main_sign_in() {
        signInButton.click();
    }

    public void sign_in_with_imdb() {
        find(By.className("list-group")).findElement(By.tagName("a")).click();
    }

    public void enter_email(String email) {
        emailInput.type(email);
    }

    public void enter_password(String password) {
        passwordInput.type(password);
    }

    public void sign_in_with_credentials() {
        signInRealButton.click();
    }

    public String getCurrentUserLoggedIn() {
        return find(By.className("navbar__user-name")).getText();
    }

    public String getAlertPrompt() {
        return find(By.className("a-alert-content")).getText();
    }
}