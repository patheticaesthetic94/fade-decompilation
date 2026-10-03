package org.fadeport.fade;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;

/** The walkthrough page on its own: what the player's "New tab ↗" link opens in a browser. */
public final class GuideActivity extends Activity {
    private WebView web;

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        web = new WebView(this);
        web.setBackgroundColor(0xff141011);
        web.setWebViewClient(new WebViewClient() {
            @Override
            public WebResourceResponse shouldInterceptRequest(WebView view, WebResourceRequest request) {
                return Assets.serve(GuideActivity.this, request.getUrl());
            }

            @Override
            public boolean shouldOverrideUrlLoading(WebView view, WebResourceRequest request) {
                if (Assets.isLocal(request.getUrl())) return false;
                HomeActivity.openExternal(GuideActivity.this, request.getUrl());
                return true;
            }
        });
        setContentView(web);
        Uri uri = getIntent().getData();
        web.loadUrl(uri != null && Assets.isLocal(uri) ? uri.toString() : Assets.ORIGIN + "walkthrough.html");
    }

    @Override
    public void onBackPressed() {
        if (web.canGoBack()) web.goBack();
        else super.onBackPressed();
    }

    static void open(Activity from, Uri uri) {
        from.startActivity(new Intent(from, GuideActivity.class).setData(uri));
    }
}
