using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BtnClickScript : MonoBehaviour 
{
    MessageBox m_msgBox;

	public void LoadBtnClicked() 
	{
        InputField loadEdit = GameObject.Find ("LoadEdit").GetComponent<InputField> ();
		if (loadEdit.text == "")
        {
            Alert("Please input stage file name!");
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
            Alert("Please input stage file name!");
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
            Alert("Please input width!");
            return;
        }
        int width = Int32.Parse(widthEdit.text);

        InputField heightEdit = GameObject.Find("HeightEdit").GetComponent<InputField>();
        if(heightEdit.text == "")
        {
            Alert("Please input height!");
            return;
        }
        int height = Int32.Parse(heightEdit.text);

        StageDataManager dataMgr = GameObject.Find("StageData").GetComponent<StageDataManager>();
        dataMgr.SetSize(width, height);
    }

    private void Alert(string info)
    {   
        if (m_msgBox == null)
            m_msgBox = (MessageBox)Resources.FindObjectsOfTypeAll(typeof(MessageBox))[0];
        
        m_msgBox.Show(info);
    }
}
