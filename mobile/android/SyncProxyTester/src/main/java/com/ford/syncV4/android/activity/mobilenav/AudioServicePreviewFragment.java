package com.ford.syncV4.android.activity.mobilenav;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;

import com.ford.syncV4.android.R;
import com.ford.syncV4.android.activity.SyncProxyTester;
import com.ford.syncV4.android.constants.Const;

import java.io.OutputStream;

/**
 * Created by Andrew Batutin on 1/23/14.
 */
public class AudioServicePreviewFragment extends Fragment implements ServicePreviewFragmentInterface {
    private static final String TAG =
            MobileNavPreviewFragment.class.getSimpleName();
    private CheckBoxState mobileNavSessionCheckBoxState;
    private Button dataStreamingButton;
    private FileStreamingLogic fileStreamingLogic;
    private SyncProxyTester context;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_audio_service_preview,
                container, true);
        context = (SyncProxyTester) getActivity();
        fileStreamingLogic = new FileStreamingLogic(this);
        return view;
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        initiateVideoCheckBox(view);
    }

    private void initiateVideoCheckBox(View view) {
        dataStreamingButton = (Button) getView().findViewById(R.id.audio_file_streaming);
        dataStreamingButton.setOnClickListener(new VideoActionListener());
        CheckBox checkBox = (CheckBox) view.findViewById(R.id.audioServiceCheckBox);
        checkBox.setOnClickListener(new MobileNaviSessionCheckBoxOnClickListener());
        mobileNavSessionCheckBoxState = new MobileNaviCheckBoxState(checkBox, getActivity());
        mobileNavSessionCheckBoxState.setStateOff();
    }

    public void onMobileNaviCheckBoxAction(View v) {
        changeMobileNaviCheckBoxState();
    }

    private void changeMobileNaviCheckBoxState() {
        if (mobileNavSessionCheckBoxState.getState().equals(CheckBoxStateValue.OFF)) {
            mobileNavSessionCheckBoxState.setStateDisabled();
            SyncProxyTester tester = (SyncProxyTester) getActivity();
            tester.startAudioService();
        } else if (mobileNavSessionCheckBoxState.getState().equals(CheckBoxStateValue.ON)) {
            SyncProxyTester tester = (SyncProxyTester) getActivity();
            tester.stopMobileNavSession();
            mobileNavSessionCheckBoxState.setStateOff();
            dataStreamingButton.setEnabled(false);
        }
    }

    public void setAudioServiceStateOff(){
        mobileNavSessionCheckBoxState.setStateOff();
        CheckBox box = (CheckBox) getView().findViewById(R.id.audioServiceCheckBox);
        box.setChecked(false);
        dataStreamingButton.setEnabled(false);
    }

    public void setAudioServiceStateOn(OutputStream stream){
        mobileNavSessionCheckBoxState.setStateOn();
        dataStreamingButton.setEnabled(true);
        fileStreamingLogic.setOutputStream(stream);
        fileStreamingLogic.createStaticFileReader();
    }

    public void dataStreamingStarted() {
        dataStreamingButton.setEnabled(false);
        dataStreamingButton.setText("Data is streaming");
    }

    public void dataStreamingStopped() {
        if (mobileNavSessionCheckBoxState.getState() == CheckBoxStateValue.ON){
            dataStreamingButton.setEnabled(true);
        }else{
            dataStreamingButton.setEnabled(false);
        }
        dataStreamingButton.setText("Start File Streaming");
    }

    private void startFileStreaming() {
        SharedPreferences prefs =
                context.getSharedPreferences(Const.PREFS_NAME, 0);
        int videoSource = prefs.getInt(Const.PREFS_KEY_NAVI_VIDEOSOURCE,
                Const.PREFS_DEFAULT_NAVI_VIDEOSOURCE);

        int videoResID = 0;
        switch (videoSource) {
            case Const.KEY_VIDEOSOURCE_MP4:
                videoResID = R.raw.faq_welcome_orientation;
                break;

            case Const.KEY_VIDEOSOURCE_H264:
                videoResID = R.raw.faq_welcome_orientation_rawh264;
                break;

            default:
                Log.e(TAG, "Unknown video source " + videoSource);
                break;
        }

        fileStreamingLogic.setFileResID(videoResID);
        fileStreamingLogic.startFileStreaming();
    }

    private class MobileNaviSessionCheckBoxOnClickListener implements View.OnClickListener{

        @Override
        public void onClick(View v) {
            onMobileNaviCheckBoxAction(v);
        }
    }

    private class VideoActionListener implements View.OnClickListener{

        @Override
        public void onClick(View v) {
            startFileStreaming();
        }
    }

}
