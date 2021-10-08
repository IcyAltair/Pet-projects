from django import forms


TEAM_MEMBERS = (("Kolesnikova, Anna", "Kolesnikova, Anna"),
                ("Yakimenko, Alexey", "Yakimenko, Alexey"),
                ("Antsupova, Daria", "Antsupova, Daria"),
                ("Hernandez, Hector", "Hernandez, Hector"),
                ("Karasev, Aleksei", "Karasev, Aleksei"),
                ("Muratov, Simar", "Muratov, Simar"),
                ("Lukashin, Alexey", "Lukashin, Alexey"),
                ("Mastache, Abraham", "Mastache, Abraham"),
                ("Millan, Sebastian", "Millan, Sebastian"),
                ("Mishin, Sergey", "Mishin, Sergey"))

BACKUP_MEMBERS = (("Lukashin, Alexey", "Lukashin, Alexey"),
                  ("Antsupova, Daria", "Antsupova, Daria"),
                  ("Yakimenko, Alexey", "Yakimenko, Alexey"),
                  ("Millan, Sebastian", "Millan, Sebastian"),
                  ("Mishin, Sergey", "Mishin, Sergey"),
                  ("Mastache, Abraham", "Mastache, Abraham"),
                  ("Kolesnikova, Anna", "Kolesnikova, Anna"),
                  ("Muratov, Simar", "Muratov, Simar"),
                  ("Hernandez, Hector", "Hernandez, Hector"),
                  ("Karasev, Aleksei", "Karasev, Aleksei"))

PROJECT_END_DATE = (("Development Support", "Development\nSupport"),
                    ("KOP: Operational Support", "KOP: Operational\nSupport"),
                    ("ITO: Development Support", "ITO: Development\nSupport"),
                    ("ITO: Development Support KOP: Operational Support", "ITO: Development\nSupport\nKOP: Operational\nSupport"))


EXAMPLES = (("DataOps\nOneID SSO\nPOC's"),
            ("[DataOps-developed the first component of auto-reporter, ready to deploy]\n[OneID SSO-made all necessary changes in OpAMs]\n[POC's-wrote a code example\
           of transfering data from Athena to PowerBi through AWS tools]"),
            ("[SEA-4506-implemented approval processes and email notifications in ROM's intake process (assignment about implementation is for the review process)]\n[SEA-4509-added test mode\
                 to frontend to automatically fill up the forms by calling a lambda function with predefined answers]"),
            ("[SEA-4506-will merge if there are no problems in the associated pull request]\n[SEA-4509-will make script to upload frontend to repository to Confluence]"),
            ("Name of other project (enter if not selected in previous point)"),
            ("[Worked on the new types of inventory files. Fixed issues with data gathering from Jira]"),
            ("[Will work on incorporating new OpsRamp data dictionary]"))

PROJECTS = (("KOP", "KOP"),
            ("ITO", "ITO"),
            ("GBS - DXG AutoOnboarding Process",
             "GBS - DXG AutoOnboarding Process"),
            ("Team Analytics and Performance", "Team Analytics and Performance"),
            ("BCD Documentation and OpAMs", "BCD Documentation and OpAMs"),
            ("Other", "Other"))


class UserForm(forms.Form):

    team_member = forms.ChoiceField(choices=TEAM_MEMBERS)
    team = forms.CharField(max_length=100, initial="Solutions Design")
    status = forms.CharField(max_length=100, initial="Active")
    team_member_backup = forms.ChoiceField(choices=BACKUP_MEMBERS)
    assigned_projects = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[0]}), max_length=300, help_text=EXAMPLES[0])
    achievements = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[1]}), max_length=300, help_text=EXAMPLES[1])
    project_end_date = forms.ChoiceField(choices=PROJECT_END_DATE)


class ProjectForm(forms.Form):

    team_member = forms.ChoiceField(choices=TEAM_MEMBERS)
    project = forms.ChoiceField(choices=PROJECTS)
    project_name = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[4]}), max_length=300, help_text=EXAMPLES[4], required=False)
    last_week_achievements = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[5]}), max_length=300, help_text=EXAMPLES[5])
    last_project_updates = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[2]}), max_length=300, help_text=EXAMPLES[2])
    next_week_achievements = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[6]}), max_length=300, help_text=EXAMPLES[6])
    next_project_updates = forms.CharField(
        widget=forms.Textarea(attrs={'placeholder': EXAMPLES[3]}), max_length=300, help_text=EXAMPLES[3])
