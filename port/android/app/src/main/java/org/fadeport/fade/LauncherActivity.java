package org.fadeport.fade;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;

/** Chooses the Classic or Remastered edition, then starts the game in this process. */
public final class LauncherActivity extends Activity {
    private static final int INK = 0xfff3e7e2, MUTED = 0xffc6aaa5, RED = 0xffd72a2a, CARD = 0xff2a1718, LINE = 0xff5a3434;
    private SharedPreferences prefs;

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        // The native runtime supports one session per process: resume it instead of starting another.
        if (FadeActivity.started) {
            startActivity(new Intent(this, FadeActivity.class).addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT));
            finish();
            return;
        }
        prefs = getSharedPreferences("launcher", MODE_PRIVATE);

        LinearLayout column = new LinearLayout(this);
        column.setOrientation(LinearLayout.VERTICAL);
        column.setGravity(Gravity.CENTER_HORIZONTAL);
        column.setPadding(dp(24), dp(40), dp(24), dp(28));

        ImageView icon = new ImageView(this);
        icon.setImageResource(R.drawable.ic_launcher_artwork);
        GradientDrawable iconShape = new GradientDrawable();
        iconShape.setCornerRadius(dp(26));
        icon.setBackground(iconShape);
        icon.setClipToOutline(true);
        column.addView(icon, new LinearLayout.LayoutParams(dp(112), dp(112)));

        TextView eyebrow = text("FADE TEAM · 2001", 12, MUTED, false);
        eyebrow.setLetterSpacing(.25f);
        eyebrow.setPadding(0, dp(22), 0, 0);
        column.addView(eyebrow);
        TextView title = text("FADE", 54, INK, false);
        title.setTypeface(Typeface.SERIF);
        title.setLetterSpacing(.18f);
        column.addView(title);
        TextView intro = text("Choose how to play", 16, MUTED, false);
        intro.setPadding(0, 0, 0, dp(22));
        column.addView(intro);

        column.addView(card("Classic", "THE ORIGINAL",
            "The 2001 game as released: 240 × 320 artwork, bitmap text and the original sounds.", "classic"));
        column.addView(card("Remastered", "ENHANCED",
            "4× artwork, crisp outline text and enhanced 48 kHz sound.", "remastered"));

        Switch lcd = new Switch(this);
        lcd.setText("Pocket PC screen filter");
        lcd.setTextColor(INK);
        lcd.setTextSize(TypedValue.COMPLEX_UNIT_SP, 15);
        lcd.setChecked(prefs.getBoolean("lcd", false));
        lcd.setOnCheckedChangeListener((v, on) -> prefs.edit().putBoolean("lcd", on).apply());
        lcd.setPadding(dp(4), dp(18), dp(4), 0);
        column.addView(lcd, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        TextView lcdNote = text("Recreates a 2001 transflective panel: its pixel grid, 16-bit colour, dim front light and slow response.", 12, MUTED, false);
        lcdNote.setGravity(Gravity.START);
        lcdNote.setPadding(dp(4), dp(4), dp(4), dp(18));
        column.addView(lcdNote, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));

        column.addView(text("Both editions share saved games. Quit from the game's menu to return here.", 12, MUTED, false));

        ScrollView scroll = new ScrollView(this);
        scroll.setFillViewport(true);
        GradientDrawable bg = new GradientDrawable(GradientDrawable.Orientation.TOP_BOTTOM, new int[] {0xff4a2a2b, 0xff1b0f10, 0xff100809});
        scroll.setBackground(bg);
        scroll.addView(column);
        setContentView(scroll);
    }

    private View card(String name, String badge, String description, String edition) {
        LinearLayout card = new LinearLayout(this);
        card.setOrientation(LinearLayout.VERTICAL);
        card.setPadding(dp(20), dp(16), dp(20), dp(18));
        GradientDrawable shape = new GradientDrawable();
        shape.setColor(CARD);
        shape.setCornerRadius(dp(14));
        shape.setStroke(dp(1), LINE);
        card.setBackground(shape);
        card.setForeground(getDrawable(android.R.drawable.list_selector_background));
        TextView b = text(badge, 11, RED, true);
        b.setLetterSpacing(.2f);
        b.setGravity(Gravity.START);
        card.addView(b);
        TextView n = text(name, 24, INK, true);
        n.setGravity(Gravity.START);
        card.addView(n);
        TextView d = text(description, 14, MUTED, false);
        d.setGravity(Gravity.START);
        d.setPadding(0, dp(4), 0, dp(10));
        card.addView(d);
        TextView play = text("Play " + name + "  →", 15, RED, true);
        play.setGravity(Gravity.START);
        card.addView(play);
        card.setClickable(true);
        card.setFocusable(true);
        card.setContentDescription("Play " + name);
        card.setOnClickListener(v -> start(edition));
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        lp.bottomMargin = dp(14);
        card.setLayoutParams(lp);
        return card;
    }

    private void start(String edition) {
        prefs.edit().putString("edition", edition).commit();   // FadeActivity applies it
        startActivity(new Intent(this, FadeActivity.class));
        finish();
    }

    private TextView text(String s, int sp, int color, boolean bold) {
        TextView t = new TextView(this);
        t.setText(s);
        t.setTextSize(TypedValue.COMPLEX_UNIT_SP, sp);
        t.setTextColor(color);
        t.setGravity(Gravity.CENTER_HORIZONTAL);
        if (bold) t.setTypeface(Typeface.DEFAULT_BOLD);
        return t;
    }

    private int dp(int v) {
        return Math.round(TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, v, getResources().getDisplayMetrics()));
    }
}
