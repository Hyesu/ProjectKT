using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BtnClickScript : MonoBehaviour 
{
    public void LoadBtnClicked() 
	{
        InputField loadEdit = GameObject.Find ("LoadEdit").GetComponent<InputField> ();
		if (loadEdit.text == "")
        {
            MessageBox.Alert("Please input stage file name!");
			return;
        }

        XmlParser xmlParser = GameObject.Find ("XmlParser").GetComponent<XmlParser> ();
        xmlParser.LoadStage (loadEdit.text);
	}

	public void SaveBtnClicked()
	{
        InputField loadEdit = GameObject.Find ("LoadEdit").GetComponent<InputField> ();
		if (loadEdit.text == "")
        {
            MessageBox.Alert("Please input stage file name!");
            return;
        }

        XmlParser xmlParser = GameObject.Find ("XmlParser").GetComponent<XmlParser> ();
		xmlParser.SaveStage (loadEdit.text);
	}

    public void ApplyBtnClicked()
    {
        InputField widthEdit = GameObject.Find("WidthEdit").GetComponent<InputField>();
        if(widthEdit.text == "")
        {
            MessageBox.Alert("Please input width!");
            return;
        }
        int width = Int32.Parse(widthEdit.text);

        InputField heightEdit = GameObject.Find("HeightEdit").GetComponent<InputField>();
        if(heightEdit.text == "")
        {
            MessageBox.Alert("Please input height!");
            return;
        }
        int height = Int32.Parse(heightEdit.text);

        StageDataManager dataMgr = GameObject.Find("StageData").GetComponent<StageDataManager>();
        dataMgr.SetSize(width, height);

        InputField bgTextureEdit = GameObject.Find("BGTextureEdit").GetComponent<InputField>();
        if(bgTextureEdit.text != "")
        {         
            ViewManager viewMgr = GameObject.Find("BGPanel").GetComponent<Image>().GetComponent<ViewManager>();
            viewMgr.SetBGTexture(bgTextureEdit.text);
        }
    }    

    public void ResetBtnClicked()
    {
        ViewManager viewMgr = GameObject.Find("BGPanel").GetComponent<Image>().GetComponent<ViewManager>();
        viewMgr.ResetTiles();
    }

    public void DetailApplyBtnClicked()
    {
        StageDataManager.GetInstance().ApplyDetailInfo();
    }
}
