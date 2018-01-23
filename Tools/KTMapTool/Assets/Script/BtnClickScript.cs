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
		Debug.Log ("Load btn clicked: " + _loadEdit.text);

		GameObject jsonParser = GameObject.Find ("JsonParser");
		JsonParser _jsonParser = jsonParser.GetComponent<JsonParser> ();
		_jsonParser.LoadFrom (_loadEdit.text);
	}

	public void SaveBtnClicked()
	{
		Debug.Log ("save clicked!");
	}
}
