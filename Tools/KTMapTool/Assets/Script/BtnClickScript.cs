using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BtnClickScript : MonoBehaviour 
{
	public void LoadBtnClicked() 
	{
		GameObject loadEdit = GameObject.Find ("LoadEdit");
		InputField _loadEdit = loadEdit.GetComponent<InputField> ();
		//Debug.Log ("LoadBtnClicked: " + _loadEdit.text);

		if (_loadEdit.text == "") 
			return;
		
		GameObject xmlParser = GameObject.Find ("XmlParser");
		XmlParser _xmlParser = xmlParser.GetComponent<XmlParser> ();
		_xmlParser.LoadStage (_loadEdit.text);
	}

	public void SaveBtnClicked()
	{
		GameObject loadEdit = GameObject.Find ("LoadEdit");
		InputField _loadEdit = loadEdit.GetComponent<InputField> ();
		//Debug.Log ("LoadBtnClicked: " + _loadEdit.text);

		if (_loadEdit.text == "") 
			return;
		
		GameObject xmlParser = GameObject.Find ("XmlParser");
		XmlParser _xmlParser = xmlParser.GetComponent<XmlParser> ();
		_xmlParser.SaveStage (_loadEdit.text);
	}
}
